# 🚀 Unit Converter Pro — Upgraded Class 11 CS Project

A **fully upgraded**, production-grade Unit Converter with 6 conversion categories,
bidirectional live input, voice recognition, dark/light themes, history, keyboard shortcuts, and PWA support.

---

## 📁 Project Files

```
unit_pro/
│
├── index.html            ← Complete frontend (HTML + CSS + JS in one file)
├── manifest.json         ← PWA manifest (makes it installable as an app)
├── sw.js                 ← Service Worker (enables offline use)
├── unit_converter_pro.c  ← Full C backend with 6 categories
├── flowchart.html        ← Interactive system flowcharts
└── README.md             ← This file
```

---

## ✨ New Features (vs Original Project)

| Feature | Original | Upgraded |
|---|---|---|
| Conversion categories | 3 | **6** |
| Total conversion pairs | 6 | **33** |
| Input mode | One-directional | **Bidirectional live** |
| Voice input | ❌ | ✅ Web Speech API |
| Unit auto-detection | ❌ | ✅ Type "100km" |
| Dark/Light toggle | ❌ | ✅ With localStorage |
| History | ❌ | ✅ Last 10, clickable |
| Keyboard shortcuts | ❌ | ✅ 8 shortcuts |
| PWA (installable) | ❌ | ✅ Works offline |
| Copy result | ❌ | ✅ Clipboard API |
| Swap button | ❌ | ✅ Instant swap |
| Color themes | 3 | **6** per type |
| C categories | 3 | **6** |
| C history | ❌ | ✅ Last 5 |
| ANSI colors in C | ❌ | ✅ Coloured output |

---

## 🌐 How to Run

### Frontend (HTML)
```
Just double-click index.html — opens in any browser.
No server, no installation needed.
```

### C Backend
```bash
# Linux / macOS
gcc unit_converter_pro.c -o unit_converter_pro -lm
./unit_converter_pro

# Windows (MinGW / Dev-C++)
gcc unit_converter_pro.c -o unit_converter_pro.exe -lm
unit_converter_pro.exe
```

### Install as Phone App (PWA)
1. Open `index.html` in Chrome/Edge
2. Look for "Install" prompt or go to browser menu → "Install app"
3. The converter is now on your home screen!

---

## ⌨️ Keyboard Shortcuts

| Key | Action |
|---|---|
| `Enter` | Convert |
| `Esc` | Clear all |
| `Ctrl+C` | Copy result |
| `S` | Swap direction |
| `T` | Toggle dark/light theme |
| `V` | Start voice input |
| `1`–`6` | Switch conversion type |
| `?` | Show shortcuts modal |

---

## 🔄 6 Conversion Categories

### 🌡️ Temperature (5 pairs)
- Celsius ↔ Fahrenheit
- Celsius ↔ Kelvin
- Fahrenheit ↔ Kelvin
- Kelvin → Celsius
- Fahrenheit → Celsius

### 📏 Distance (6 pairs)
- Meter ↔ Kilometer
- Meter → Centimeter
- Meter → Feet
- Kilometer → Mile
- Centimeter → Inch

### ⚖️ Mass (6 pairs)
- Kilogram ↔ Gram
- Kilogram → Pound
- Pound → Kilogram
- Gram → Milligram
- Kilogram → Metric Ton

### 💨 Speed (5 pairs)
- m/s ↔ km/h
- km/h ↔ mph
- m/s → mph

### 📐 Area (5 pairs)
- m² → cm²
- m² → ft²
- km² → mi²
- Hectare → m²
- Acre → m²

### ⏱️ Time (6 pairs)
- Second → Minute
- Minute → Hour
- Hour → Day
- Second → Hour
- Day → Week
- Second → Millisecond

---

## 📐 Conversion Formulas Reference

### Temperature
```
Celsius → Fahrenheit:  F = (C × 9/5) + 32
Fahrenheit → Celsius:  C = (F − 32) × 5/9
Celsius → Kelvin:      K = C + 273.15
Fahrenheit → Kelvin:   K = (F−32) × 5/9 + 273.15
```

### Distance
```
km  = m  ÷ 1000
cm  = m  × 100
ft  = m  × 3.28084
mi  = km × 0.621371
in  = cm ÷ 2.54
```

### Mass
```
g   = kg × 1000
lb  = kg × 2.20462
mg  = g  × 1000
t   = kg ÷ 1000
```

### Speed
```
km/h = m/s × 3.6
mph  = km/h × 0.621371
mph  = m/s  × 2.23694
```

### Area
```
cm² = m²  × 10,000
ft² = m²  × 10.7639
mi² = km² × 0.386102
m²  = ha  × 10,000
m²  = acre × 4046.86
```

### Time
```
min  = s   ÷ 60
h    = min ÷ 60
day  = h   ÷ 24
h    = s   ÷ 3600
week = day ÷ 7
ms   = s   × 1000
```

---

## 🔗 Frontend–Backend Connection

See `flowchart.html` for an interactive diagram. Three methods:

1. **File Handling** (Easiest for Class 11):
   - JS writes the value to `input.txt`
   - C reads `input.txt`, converts, writes `output.txt`
   - JS reads `output.txt` and shows the result

2. **CGI** (Intermediate):
   - Apache web server runs the C program
   - C reads input from environment variables
   - C prints HTML output directly

3. **REST API** (Advanced):
   - Python Flask wraps the C program
   - JS fetches from the Python API
   - Python calls C via `subprocess` and returns JSON

---

## ❓ Viva Questions & Answers (10 Total)

### Q1. What does bidirectional conversion mean in this project?
**Answer:** It means both input fields are linked. When you type in field A, field B updates instantly, and when you type in field B, field A updates. This is achieved using JavaScript `addEventListener("input")` on both fields, with a flag variable `updatingInputs` to prevent infinite loops where each field keeps triggering the other.

---

### Q2. What is a PWA and how did you implement it?
**Answer:** PWA stands for **Progressive Web App**. It is a website that can be installed on a phone or computer like a native app and works offline. We implemented it using:
- `manifest.json` — tells the browser the app's name, icon, and theme color
- `sw.js` (Service Worker) — a background script that caches all files so they work without internet
The browser shows an "Install" button automatically when both files are present.

---

### Q3. What is localStorage and how is it used in the history feature?
**Answer:** `localStorage` is a browser feature that stores data as key-value pairs permanently — even after closing the browser. In this project:
- Every successful conversion is stored with `localStorage.setItem("uc_history_v2", JSON.stringify(array))`
- When the page loads, history is restored with `localStorage.getItem("uc_history_v2")`
- The last type selected is also saved so the app "remembers" what you were doing

---

### Q4. How does the voice input feature work?
**Answer:** It uses the browser's built-in `Web Speech API`. Specifically, the `SpeechRecognition` object listens for spoken words. When the user clicks the microphone button:
1. `recognition.start()` begins listening
2. `recognition.onresult` fires when speech is detected
3. We use a RegEx pattern to extract the number from the transcript
4. The extracted number is placed in the input field and the conversion fires automatically
This works best in Google Chrome.

---

### Q5. What is the purpose of `snprintf()` in the C program? Why not use `printf()` directly?
**Answer:** `snprintf(dest, size, format, ...)` writes a formatted string into a character array (buffer) instead of printing to screen. We use it to build strings like `"100.00 kg"` in the `from_str` and `to_str` variables, which are then passed to the `printResult()` and `addToHistory()` functions. If we used `printf()`, the data would go to screen immediately and we couldn't store or reuse it.

---

### Q6. What is the difference between `%d` and `%lf` in C's `scanf()`?
**Answer:**
- `%d` reads an **integer** (whole number only, e.g. 5, 100, -3)
- `%lf` reads a **double** (decimal number, e.g. 3.14, 100.5, -0.001)

In this project we use `%d` for the menu choice and direction (which are always whole numbers) and `%lf` for the actual value to convert (which might have decimal places like 36.6°C or 1.5 km).

---

### Q7. What does the `marker-end` attribute do in the SVG flowchart?
**Answer:** `marker-end` attaches an arrowhead to the end of an SVG line or path element. We defined the arrowhead shape inside a `<marker>` element and gave it an id (like `arr`). Then on each `<line>`, we write `marker-end="url(#arr)"` to place that arrow at the endpoint. This creates the flow arrows in the flowchart without needing any images.

---

### Q8. Why do we use `CSS Custom Properties (variables)` in the stylesheet?
**Answer:** CSS variables (e.g. `--accent: #ff6b35`) allow us to change **one value** and have it automatically apply everywhere it's used. In this project, when the user switches to "Distance" mode, we simply change `--accent` to `#3ecfcf` (cyan) on the body element, and every element that uses `var(--accent)` — the button, border, glow, unit label — all update at once. Without variables, we'd need to update 15+ individual CSS rules.

---

### Q9. What is the role of the Service Worker in a PWA?
**Answer:** A Service Worker is a JavaScript file that runs in the background, separate from the main webpage. It acts like a **local proxy**:
- On first visit: it downloads and caches all files (`index.html`, fonts, etc.)
- On later visits (even offline): it intercepts network requests and serves from cache
- This is why the app works without internet connection after first load
It uses three lifecycle events: `install` (cache files), `activate` (clean old caches), and `fetch` (intercept requests).

---

### Q10. If you had to add a new conversion type (e.g. Currency), what changes would you make?
**Answer:** For the **HTML/JS frontend**:
1. Add a new entry to the `CONVERSIONS` object with type `currency`, color, icon, and pairs array
2. Add a new button in the type grid HTML
3. No other changes needed — the rest of the code (UI update, history, themes) works automatically

For the **C backend**:
1. Add a new `case 7` in the main `switch`
2. Write a new `convertCurrency()` function
3. Update the menu display

This shows good **modular design** — new features can be added without rewriting existing code.

---

## 🏆 Technologies Used

| Technology | Purpose |
|---|---|
| HTML5 | Page structure and semantic elements |
| CSS3 | Styling, animations, CSS variables, responsive grid |
| JavaScript (ES6+) | Logic, event handling, APIs |
| Web Speech API | Voice input |
| Clipboard API | Copy to clipboard |
| localStorage API | History + theme persistence |
| Service Worker API | Offline/PWA support |
| C Language | Terminal-based backend converter |
| ANSI Escape Codes | Coloured C terminal output |
| SVG | Flowchart diagrams |
| Google Fonts | Typography (Syne + Space Mono) |

---

*Class 11 Computer Science Project — Upgraded Edition*
*HTML + CSS + JavaScript + C*
