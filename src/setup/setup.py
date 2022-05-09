import PySimpleGUI as sg
import os

sg.theme('DarkBlue3')      
sg.set_options(element_padding=(6,3),margins = (30,30)) 

layout = [[sg.Text('Motion Perfection 1.0', font="Avenir 20")],
    [sg.Text("Select the folder in which you want Motion Perfection 1.0 installed.")],
        [sg.Text("The installation will create a folder named \'MotionPerfection\' at your selected destination.")],
                [sg.InputText(size=(60, 1), key="dest"),
                sg.FolderBrowse()],[sg.Push(), sg.Button('Install',pad = (0,20)),sg.Push()]]

window = sg.Window("Motion Perfection 1.0 Installer", layout)

#Event loop
while True:
    event, values = window.read()
    if event == 'Exit' or event == sg.WIN_CLOSED:
        break
    if event == "Install":
        window['Install'].update('Installing...')
        sg.popup('The installation will take around 5 minutes to complete. Close this popup window to continue.')
        os.system(r'createWorkingFolder.cmd ' + values['dest'].replace("/","\\") + r'\MotionPerfection ')
        sg.popup('Installation completed. Check your destination folder to verify')
        break

window.close()
