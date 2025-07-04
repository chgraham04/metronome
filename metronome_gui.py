import tkinter as tk
from tkinter import ttk, messagebox
import subprocess

# Globals
process = None
bpm_value = 100

def start_metronome():
    global process
    try:
        num = int(numerator_var.get())
        denom = int(denominator_var.get())
        args = [
            "cmake-build-debug/metronome_engine.exe",
            str(bpm_value),
            str(num),
            str(denom),
            str(int(accent_enabled.get()))
        ]
        process = subprocess.Popen(args)
        play_btn.config(image=pause_img)
        play_btn.image = pause_img
    except Exception as e:
        messagebox.showerror("Error", str(e))

def stop_metronome():
    global process
    if process:
        process.terminate()
        process = None
        play_btn.config(image=play_img)
        play_btn.image = play_img

def toggle_metronome():
    if process:
        stop_metronome()
    else:
        start_metronome()

def on_bpm_change(val):
    global bpm_value
    bpm_value = int(float(val))
    bpm_label.config(text=f"{bpm_value} bpm")

# --- UI Setup ---
window = tk.Tk()
window.title("Metronome")
window.geometry("450x300")
bg_color = "#a3b18a"
window.configure(bg=bg_color)

accent_enabled = tk.BooleanVar(value=True)

# Top-left accent toggle
top_frame = tk.Frame(window, bg=bg_color)
top_frame.pack(fill=tk.X, pady=(5, 0))
accent_check = tk.Checkbutton(top_frame, text="*", variable=accent_enabled,
                              bg=bg_color, font=("Arial", 12), highlightthickness=0, bd=0)
accent_check.pack(side=tk.LEFT, padx=10)

# BPM label and slider
bpm_label = tk.Label(window, text=f"{bpm_value} bpm", font=("Georgia", 20), bg=bg_color)
bpm_label.pack(pady=(5, 5))

bpm_slider = tk.Scale(window, from_=0, to=330, orient=tk.HORIZONTAL, command=on_bpm_change,
                      showvalue=0, length=300, resolution=1, bg=bg_color,
                      highlightthickness=0, troughcolor="white")
bpm_slider.set(bpm_value)
bpm_slider.pack()

# --- Time Signature Section ---
ts_frame = tk.Frame(window, bg=bg_color)
ts_frame.pack(pady=(20, 10))

numerator_var = tk.StringVar(value="4")
denominator_var = tk.StringVar(value="4")

numerator_dropdown = ttk.Combobox(ts_frame, textvariable=numerator_var, width=5,
                                  values=[str(i) for i in range(2, 257)], state="readonly")
numerator_dropdown.grid(row=0, column=0, padx=(0, 8))

slash_label = tk.Label(ts_frame, text="/", font=("Georgia", 20), bg=bg_color)
slash_label.grid(row=0, column=1, padx=5)

denominator_dropdown = ttk.Combobox(ts_frame, textvariable=denominator_var, width=5,
                                    values=["4", "8", "16", "32"], state="readonly")
denominator_dropdown.grid(row=0, column=2, padx=(8, 0))

# --- Load Play/Pause Icons (100x100)
play_img = tk.PhotoImage(file="play.png")
pause_img = tk.PhotoImage(file="pause.png")

# --- Play/Pause Button (100x100)
play_btn = tk.Button(
    window,
    image=play_img,
    command=toggle_metronome,
    relief="raised",
    borderwidth=4,
    bg="#e0e0e0",
    activebackground="#cfcfcf"
)
play_btn.image = play_img  # Prevent garbage collection
play_btn.place(relx=0.5, rely=0.75, anchor="center", width=100, height=100)

# Spacebar toggle
window.bind("<space>", lambda e: toggle_metronome())

window.mainloop()
