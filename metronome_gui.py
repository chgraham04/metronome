import tkinter as tk
from tkinter import ttk
import subprocess

# Global variables
process = None  # For tracking the metronome process
bpm_value = 120
time_signature = "4/4"

# Start the C++ metronome process
def start_metronome():
    global process, bpm_value, time_signature
    if process is None:
        num_beats = int(time_signature.split("/")[0])
        process = subprocess.Popen(["./metronome_engine", str(bpm_value), str(num_beats)])

# Stop the metronome process
def stop_metronome():
    global process
    if process:
        process.terminate()
        process = None

# Toggle play/pause
def toggle_metronome(event=None):
    if process:
        stop_metronome()
    else:
        start_metronome()

# Update BPM from slider
def on_bpm_change(val):
    global bpm_value
    bpm_value = int(float(val))
    bpm_label.config(text=f"{bpm_value} BPM")

# Update time signature
def on_time_signature_change(event):
    global time_signature
    time_signature = time_signature_var.get()

# Tkinter Window
window = tk.Tk()
window.title("C++ Metronome Controller")
window.geometry("400x300")
window.configure(bg="#a3b18a")
window.bind("<space>", toggle_metronome)

# Title
tk.Label(window, text="Metronome", font=("Georgia", 24), bg="#a3b18a").pack(pady=10)

# BPM Slider
tk.Label(window, text="BPM", font=("Georgia", 14), bg="#a3b18a").pack()
bpm_slider = tk.Scale(window, from_=0, to=330, orient=tk.HORIZONTAL, command=on_bpm_change)
bpm_slider.set(120)
bpm_slider.pack()
bpm_label = tk.Label(window, text="120 BPM", font=("Georgia", 12), bg="#a3b18a")
bpm_label.pack()

# Time Signature Dropdown
tk.Label(window, text="Time Signature", font=("Georgia", 14), bg="#a3b18a").pack(pady=(10, 0))
time_signature_var = tk.StringVar(value="4/4")
time_dropdown = ttk.Combobox(window, textvariable=time_signature_var, values=["4/4", "3/4", "6/8"])
time_dropdown.pack()
time_dropdown.bind("<<ComboboxSelected>>", on_time_signature_change)

# Play/Pause Button
play_pause_btn = tk.Button(window, text="Play / Pause (Space)", font=("Georgia", 14), command=toggle_metronome)
play_pause_btn.pack(pady=20)

window.mainloop()