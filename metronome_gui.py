import tkinter as tk
from tkinter import ttk, messagebox
import subprocess
import os

# Globals
process = None
bpm_value = 100
bpm_hold_job = None
bpm_change_direction = 0
script_dir = os.path.dirname(os.path.abspath(__file__))
exe_path = os.path.join(script_dir, "cmake-build-debug", "metronome_engine.exe")


def start_metronome():
    global process
    try:
        num = int(numerator_var.get())
        denom = int(denominator_var.get())
        args = [
            exe_path,
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

def toggle_time_signature_state():
    state = "readonly" if accent_enabled.get() else "disabled"
    numerator_dropdown.config(state=state)
    denominator_dropdown.config(state=state)

def toggle_accent_checkbox(event=None):
    current = accent_enabled.get()
    accent_enabled.set(not current)
    toggle_time_signature_state()

def update_bpm(amount):
    global bpm_value
    new_bpm = max(0, min(330, bpm_value + amount))
    if new_bpm != bpm_value:
        bpm_value = new_bpm
        bpm_slider.set(bpm_value)
        bpm_label.config(text=f"{bpm_value} bpm")

def hold_bpm_change():
    global bpm_hold_job
    if bpm_change_direction != 0:
        update_bpm(bpm_change_direction)
        bpm_hold_job = window.after(50, hold_bpm_change)

def on_arrow_press(event):
    global bpm_change_direction, bpm_hold_job

    if bpm_hold_job:
        window.after_cancel(bpm_hold_job)

    if event.keysym == "Up":
        update_bpm(1)
        bpm_change_direction = 1
    elif event.keysym == "Down":
        update_bpm(-1)
        bpm_change_direction = -1
    else:
        return

    bpm_hold_job = window.after(400, hold_bpm_change)

def on_arrow_release(event):
    global bpm_hold_job, bpm_change_direction
    bpm_change_direction = 0
    if bpm_hold_job:
        window.after_cancel(bpm_hold_job)
        bpm_hold_job = None

# --- UI Setup ---
window = tk.Tk()
window.title("Metronome")
window.geometry("500x360")
bg_color = "#a3b18a"
window.configure(bg=bg_color)

accent_enabled = tk.BooleanVar(value=True)

# Top-left accent toggle
top_frame = tk.Frame(window, bg=bg_color)
top_frame.pack(fill=tk.X, pady=(5, 0))
accent_check = tk.Checkbutton(top_frame, text="*", variable=accent_enabled,
                              bg=bg_color, font=("Arial", 12),
                              highlightthickness=0, bd=0,
                              command=toggle_time_signature_state)
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

# --- Load Play/Pause Icons (64x64)
play_img = tk.PhotoImage(file="play.png")
pause_img = tk.PhotoImage(file="pause.png")

# --- Play/Pause Button (Invisible border, 64x64)
play_btn = tk.Button(
    window,
    image=play_img,
    command=toggle_metronome,
    relief="flat",
    borderwidth=0,
    bg=bg_color,
    activebackground=bg_color,
    highlightthickness=0
)
play_btn.image = play_img
play_btn.place(relx=0.5, rely=0.63, anchor="center", width=64, height=64)

# Key bindings
window.bind("<space>", lambda e: toggle_metronome())
window.bind("<Return>", toggle_accent_checkbox)
window.bind("<Up>", on_arrow_press)
window.bind("<Down>", on_arrow_press)
window.bind("<KeyRelease-Up>", on_arrow_release)
window.bind("<KeyRelease-Down>", on_arrow_release)

# Disable dropdowns if accent is off at startup
toggle_time_signature_state()

window.mainloop()
