import tkinter as tk
from tkinter import ttk, messagebox
import subprocess

# Globals
process = None
bpm_value = 100
time_signatures = ["4/4"]

# Initialize root before creating any Tkinter variables
window = tk.Tk()
window.title("Metronome")
window.geometry("500x300")
bg_color = "#a3b18a"
window.configure(bg=bg_color)

accent_enabled = tk.BooleanVar(value=True)

# ---- Function Definitions ----

def start_metronome():
    global process
    try:
        num, denom = map(int, time_signature_var.get().split("/"))
        args = [
            "cmake-build-debug/metronome_engine.exe",
            str(bpm_value),
            str(num),
            str(denom),
            str(int(accent_enabled.get()))
        ]
        process = subprocess.Popen(args)
    except Exception as e:
        messagebox.showerror("Error", str(e))

def stop_metronome():
    global process
    if process:
        process.terminate()
        process = None

def toggle_metronome():
    if process:
        stop_metronome()
        play_btn.config(text="▶️")
    else:
        start_metronome()
        play_btn.config(text="⏸️")

def on_bpm_change(val):
    global bpm_value
    bpm_value = int(float(val))
    bpm_label.config(text=f"{bpm_value} bpm")

def on_time_signature_enter(event=None):
    new_ts = time_signature_entry.get().strip()
    if "/" in new_ts:
        try:
            num, denom = map(int, new_ts.split("/"))
            if num >= 2 and denom in [4, 8, 16]:
                if new_ts not in time_signatures:
                    time_signatures.append(new_ts)
                    time_dropdown['values'] = time_signatures
                time_signature_var.set(new_ts)
                time_signature_entry.delete(0, tk.END)
            else:
                raise ValueError
        except:
            messagebox.showerror("Invalid Time Signature", "Use format like 4/4, 6/8, with denom 4/8/16 and num ≥ 2")
    else:
        messagebox.showerror("Invalid Input", "Format must be like 3/4")

# ---- Layout ----

# Top bar (accent toggle only now)
top_frame = tk.Frame(window, bg=bg_color)
top_frame.pack(fill=tk.X, pady=(5, 0))

accent_check = tk.Checkbutton(
    top_frame, text="*", variable=accent_enabled,
    bg=bg_color, font=("Arial", 12), highlightthickness=0, bd=0
)
accent_check.pack(side=tk.LEFT, padx=10)

# BPM display
bpm_label = tk.Label(window, text=f"{bpm_value} bpm", font=("Georgia", 20), bg=bg_color)
bpm_label.pack(pady=(5, 5))

# BPM Slider
bpm_slider = tk.Scale(window, from_=0, to=330, orient=tk.HORIZONTAL,
                      command=on_bpm_change, showvalue=0, length=300,
                      resolution=1, bg=bg_color, highlightthickness=0, troughcolor="white")
bpm_slider.set(bpm_value)
bpm_slider.pack()

# Time Signature section
ts_frame = tk.Frame(window, bg=bg_color)
ts_frame.pack(pady=(10, 5))

tk.Label(ts_frame, text="Time Signature:", font=("Georgia", 12), bg=bg_color).grid(row=0, column=0, padx=5)
time_signature_var = tk.StringVar(value="4/4")
time_dropdown = ttk.Combobox(ts_frame, textvariable=time_signature_var, values=time_signatures, width=6)
time_dropdown.grid(row=0, column=1, padx=5)

time_signature_entry = ttk.Entry(ts_frame, width=6)
time_signature_entry.grid(row=0, column=2, padx=5)
time_signature_entry.bind("<Return>", on_time_signature_enter)

# Play/Pause Button
play_btn = tk.Button(window, text="▶️", font=("Arial", 24), width=4, command=toggle_metronome)
play_btn.pack(pady=10)

# Bind spacebar
window.bind("<space>", lambda e: toggle_metronome())

window.mainloop()
