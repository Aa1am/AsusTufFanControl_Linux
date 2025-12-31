#!/bin/bash

CONFIG_FILE="/etc/asus_battery_limit.conf"
DEFAULT_LIMIT=80

# 1. Read Config
if [ -f "$CONFIG_FILE" ]; then
    LIMIT=$(cat "$CONFIG_FILE")
else
    echo "Config file not found, using default $DEFAULT_LIMIT"
    LIMIT=$DEFAULT_LIMIT
fi

# Validate integer
if ! [[ "$LIMIT" =~ ^[0-9]+$ ]]; then
    echo "Invalid limit value: $LIMIT"
    exit 1
fi

# Clamp logic
if [ "$LIMIT" -lt 60 ]; then LIMIT=60; fi
if [ "$LIMIT" -gt 100 ]; then LIMIT=100; fi

echo "Applying Battery Limit: $LIMIT%"

# Identify Battery Path for Verification/Fallback
BAT_PATH=""
if [ -d "/sys/class/power_supply/BAT1" ]; then
    BAT_PATH="/sys/class/power_supply/BAT1"
elif [ -d "/sys/class/power_supply/BAT0" ]; then
    BAT_PATH="/sys/class/power_supply/BAT0"
fi

SUCCESS=0

# 2. Try asusctl first (Preferred)
if command -v asusctl &> /dev/null; then
    echo "Using asusctl to set limit..."
    asusctl -c "$LIMIT"
    # Wait a moment for it to apply
    sleep 1
    
    # Verify if it actually worked
    if [ -n "$BAT_PATH" ]; then
        CURRENT=$(cat "$BAT_PATH/charge_control_end_threshold" 2>/dev/null)
        if [ "$CURRENT" -eq "$LIMIT" ]; then
            echo "Success: Limit confirmed as $CURRENT via asusctl"
            SUCCESS=1
        else
            echo "Warning: asusctl ran but limit is $CURRENT (wanted $LIMIT). Trying fallback..."
        fi
    else
        # If we can't verify, we assume asusctl might have worked, but usually BAT_PATH should exist.
        echo "Warning: Cannot verify asusctl result (no BAT path)."
    fi
fi

# 3. Fallback: Direct Kernel Write (If asusctl failed or verification failed)
if [ "$SUCCESS" -eq 0 ]; then
    if [ -z "$BAT_PATH" ]; then
        echo "Error: No Battery (BAT0/BAT1) found! Cannot apply limit."
        exit 1
    fi

    echo "Using direct sysfs write to $BAT_PATH..."
    echo "$LIMIT" > "$BAT_PATH/charge_control_end_threshold"
    
    # 4. Verify Fallback
    CURRENT=$(cat "$BAT_PATH/charge_control_end_threshold")
    if [ "$CURRENT" -eq "$LIMIT" ]; then
        echo "Success: Limit set to $CURRENT using direct sysfs write"
    else
        echo "Error: Failed to set limit. Readback: $CURRENT"
        exit 1
    fi
fi

exit 0
