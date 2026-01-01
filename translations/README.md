# Multi-Language Support (i18n) Guide

## 🌍 Global Language Support
The application detects your system language automatically. If you want to force a specific language, use the commands below.

## 🚀 How to Run in Specific Languages
Copy and run the command for your preferred language:

### 🇮🇳 Tamil (தமிழ்)
```bash
sudo LC_ALL=ta_IN.UTF-8 ./AsusTufFanControl_Linux
```

### 🇧🇩 Bengali (বাংলা)
```bash
sudo LC_ALL=bn_IN.UTF-8 ./AsusTufFanControl_Linux
```

### 🇪🇸 Spanish (Español)
```bash
sudo LC_ALL=es_ES.UTF-8 ./AsusTufFanControl_Linux
```

### 🇫🇷 French (Français)
```bash
sudo LC_ALL=fr_FR.UTF-8 ./AsusTufFanControl_Linux
```

### 🇩🇪 German (Deutsch)
```bash
sudo LC_ALL=de_DE.UTF-8 ./AsusTufFanControl_Linux
```

### 🇨🇳 Chinese (中文)
```bash
sudo LC_ALL=zh_CN.UTF-8 ./AsusTufFanControl_Linux
```

### 🇯🇵 Japanese (日本語)
```bash
sudo LC_ALL=ja_JP.UTF-8 ./AsusTufFanControl_Linux
```

### 🇰🇷 Korean (한국어)
```bash
sudo LC_ALL=ko_KR.UTF-8 ./AsusTufFanControl_Linux
```

### 🇷🇺 Russian (Русский)
```bash
sudo LC_ALL=ru_RU.UTF-8 ./AsusTufFanControl_Linux
```

### 🇵🇹 Portuguese (Português)
```bash
sudo LC_ALL=pt_BR.UTF-8 ./AsusTufFanControl_Linux
```

### 🇮🇹 Italian (Italiano)
```bash
sudo LC_ALL=it_IT.UTF-8 ./AsusTufFanControl_Linux
```

### 🇸🇦 Arabic (العربية)
```bash
sudo LC_ALL=ar_SA.UTF-8 ./AsusTufFanControl_Linux
```

### 🇹🇷 Turkish (Türkçe)
```bash
sudo LC_ALL=tr_TR.UTF-8 ./AsusTufFanControl_Linux
```

### 🇮🇩 Indonesian (Bahasa Indonesia)
```bash
sudo LC_ALL=id_ID.UTF-8 ./AsusTufFanControl_Linux
```

### 🇻🇳 Vietnamese (Tiếng Việt)
```bash
sudo LC_ALL=vi_VN.UTF-8 ./AsusTufFanControl_Linux
```

### 🇵🇱 Polish (Polski)
```bash
sudo LC_ALL=pl_PL.UTF-8 ./AsusTufFanControl_Linux
```

### 🇵🇰 Urdu (اردو)
```bash
sudo LC_ALL=ur_PK.UTF-8 ./AsusTufFanControl_Linux
```

### 🇮🇳 Punjabi (ਪੰਜਾਬੀ)
```bash
sudo LC_ALL=pa_IN.UTF-8 ./AsusTufFanControl_Linux
```

### 🇮🇷 Persian (فارسی)
```bash
sudo LC_ALL=fa_IR.UTF-8 ./AsusTufFanControl_Linux
```

### 🇰🇪 Swahili (Kiswahili)
```bash
sudo LC_ALL=sw_KE.UTF-8 ./AsusTufFanControl_Linux
```

### 🇮🇳 Marathi (मराठी)
```bash
sudo LC_ALL=mr_IN.UTF-8 ./AsusTufFanControl_Linux
```
### 🇮🇳 Hindi (हिन्दी)
```bash
sudo LC_ALL=hi_IN.UTF-8 ./AsusTufFanControl_Linux
```
---

## 📊 Available Languages Status

| Language | Code | Status |
|----------|------|--------|
| **Tamil** | `ta` | ✅ Complete |
| Bengali  | `bn` | ✅ Complete |
| Spanish  | `es` | ✅ Complete |
| French   | `fr` | ✅ Complete |
| German   | `de` | ✅ Complete |
| Chinese  | `zh` | ✅ Complete |
| Japanese | `ja` | ✅ Complete |
| Russian  | `ru` | ✅ Complete |
| Portuguese | `pt` | ✅ Complete |
| Korean   | `ko` | ✅ Complete |
| Italian  | `it` | ✅ Complete |
| Arabic   | `ar` | ✅ Complete |
| Turkish  | `tr` | ✅ Complete |
| Indonesian | `id` | ✅ Complete |
| Vietnamese | `vi` | ✅ Complete |
| Polish   | `pl` | ✅ Complete |
| Urdu     | `ur` | ✅ Complete |
| Punjabi  | `pa` | ✅ Complete |
| Persian  | `fa` | ✅ Complete |
| Swahili  | `sw` | ✅ Complete |
| Marathi  | `mr` | ✅ Complete |
| Hindi    | `hi` | ✅ Complete |
| English  | `en` | ✅ Default (Source) |

---

## 🛠️ For Developers & Translators

### Automated Build System
We use a custom automation script (`patch_translations.py`) integrated into CMake.
**You do not need to manually run `lupdate` or `lrelease`.**

When you run `cmake ..`, the system automatically:
1. **Injects missing keys:** Ensures dynamic strings (like "Mode: Silent", "Maximum 100%") are present in all `.ts` files.
2. **Updates Translations:** Applies latest translations from the central dictionary.
3. **Compiles:** Generates `.qm` files for the application.

### How to Add a New Language
1. Add your language code to `CMakeLists.txt`.
2. Add your language dictionary to `patch_translations.py`.
3. Build the app!

### Troubleshooting
**Translation Not Loading?**
Run `cmake ..` in your build directory to trigger the patcher.

**Missing Strings?**
If a button is still in English, check `patch_translations.py` and add the string to `EXTRA_FINAL`.
