import PySimpleGUI as sg
import os

sg.theme('DarkTeal11')      
sg.set_options(element_padding=(6,3),margins = (30,30)) 


''' 
Select a file to read
'''
folder = ""
padding = 10
#GUI layout
tab1_layout = [

                [sg.Text("Model Video:")],
                [sg.InputText(size=(60, 1),key="modelVideo"),
                sg.FileBrowse()],
                [sg.Radio('Time Offset (s):', 1, key = 'manualModel', enable_events=True),
                sg.InputText(size=(15, 1), key = 'modelTimeOffset', disabled = True)],
                [sg.Radio('Trigger Frame:', 1, key = 'autoModel', enable_events=True), sg.InputText(size=(42, 1), key = 'triggerFrameModel', disabled = True),
                sg.FileBrowse(key = 'browseTriggerModel', disabled = True)],
                [sg.Push(), sg.Button('Prepare Model Poses',pad = (0,20)),sg.Push()]
                ]

tab2_layout = [
                [sg.Text("Focal Video:")],
                [sg.InputText(size=(60, 1),key="focalVideo"),
                sg.FileBrowse()],
                [sg.Radio('Time Offset (s):', 1, key = 'manualFocal', enable_events=True),
                sg.InputText(size=(15, 1), key = 'focalTimeOffset', disabled = True)],
                [sg.Radio('Trigger Frame:', 1, key = 'autoFocal', enable_events=True), sg.InputText(size=(42, 1), key = 'triggerFrameFocal', disabled = True),
                sg.FileBrowse(key = 'browseTriggerFocal', disabled = True)],
                [sg.Text("PDF Filename:"), sg.InputText(size=(15, 1),pad = (2,12), key = 'fileName'), sg.Text(".pdf", pad = (0,12)),],
                [sg.Push(), sg.Button('Prepare PDFs',pad = (0,20)),sg.Push()]
                ]

                

layout = [
                [sg.Push(), sg.Text("Motion Perfection 1.0",font="Avenir 20", pad = (0,10)),sg.Push()],

                [sg.Text("Working Folder:")],
                [sg.InputText(size=(60, 1), key="workFolder"),
                sg.FolderBrowse()],
                [sg.Text("Frame Extraction List (.txt):")],
                [sg.InputText(size=(60, 1), key = 'timings'),
                sg.FileBrowse()],
                [sg.HorizontalSeparator(pad = (0,20))],
                [sg.TabGroup([[sg.Tab('prepare Model Poses', tab1_layout), sg.Tab('Create PDFs for Focal Participants', tab2_layout)]])]]
#WINDOW generation
window = sg.Window("Motion Perfection 1.0", layout)

#Event loop
while True:
    event, values = window.read()
    if event == 'Exit' or event == sg.WIN_CLOSED:
        break
    elif event.startswith('Prepare Model'):
        if values['manualModel']:
            os.system(r'extractAndPrepareModelPoses.cmd ' + values['workFolder'].replace("/","\\") + r'\frames ' + values['workFolder'].replace("/","\\") + r'\modelposes ' + values['timings'].replace("/","\\") + ' ' + values['modelVideo'].replace("/","\\") + ' ' + values['modelTimeOffset'])
            sg.popup('Process completed. Check your output folder to verify.')
        else:
            os.system(r'extractAndPrepareModelPosesTrigger.cmd ' + values['workFolder'].replace("/","\\") + r'\frames ' + values['workFolder'].replace("/","\\") + r'\modelposes ' + values['timings'].replace("/","\\") + ' ' + values['modelVideo'].replace("/","\\") + ' ' + values['triggerFrameModel'].replace("/","\\"))
            sg.popup('Process completed. Check your output folder to verify.')
    elif event.startswith('Prepare PDFs'):
        
        if values['manualFocal']:
            sg.popup('This will take a few minutes, close this popup window to proceed.')
            os.system(r'extractAndPrepareFocalPoses.cmd ' + values['workFolder'].replace("/","\\") + r'\frames ' + values['workFolder'].replace("/","\\") + r'\modelposes ' + values['timings'].replace("/","\\") + ' ' + values['focalVideo'].replace("/","\\") + ' ' + values['focalTimeOffset'] + ' ' + values['workFolder'].replace("/","\\") + r'\PDFs ' + ' ' + values['fileName'])
            sg.popup('Process completed. Check your output folder to verify.')

        else:
            sg.popup('This will take a few minutes, close this popup window to proceed.')
            os.system(r'extractAndPrepareFocalPosesTrigger.cmd ' + values['workFolder'].replace("/","\\") + r'\frames ' + values['workFolder'].replace("/","\\") + r'\modelposes ' + values['timings'].replace("/","\\") + ' ' + values['focalVideo'].replace("/","\\") + ' ' + values['triggerFrameFocal'].replace("/","\\") + ' ' + values['workFolder'].replace("/","\\") + r'\PDFs ' + ' ' + values['fileName'])    
            sg.popup('Process completed. Check your output folder to verify.')

    elif event == 'autoModel':
        if values['autoModel']:
            window['modelTimeOffset'].update(disabled=True)
            # window['modelTimeOffset'].update('')
            window['triggerFrameModel'].update(disabled=False)
            # window['triggerFrameModel'].update('')
            window['browseTriggerModel'].update(disabled=False)
            


    elif event == 'manualModel':
            window['modelTimeOffset'].update(disabled=False)
            # window['modelTimeOffset'].update('')
            window['triggerFrameModel'].update(disabled=True)
            # window['triggerFrameModel'].update('')
            window['browseTriggerModel'].update(disabled=True)

    elif event == 'autoFocal':
        if values['autoFocal']:
            window['focalTimeOffset'].update(disabled=True)
            # window['focalTimeOffset'].update('')
            window['triggerFrameFocal'].update(disabled=False)
            # window['triggerFrameFocal'].update('')
            window['browseTriggerFocal'].update(disabled=False)

    elif event == 'manualFocal':
            window['focalTimeOffset'].update(disabled=False)
            # window['focalTimeOffset'].update('')
            window['triggerFrameFocal'].update(disabled=True)
            # window['triggerFrameFocal'].update('')
            window['browseTriggerFocal'].update(disabled=True)


window.close()


    # [[      sg.FileBrowse(key="file"),
    #         sg.Text("File"),
    #         sg.InputText()],
    #     [sg.Submit(key="submit"), sg.Cancel("Exit")]],

    # [[
    #         sg.FileBrowse(key="file"),
    #         sg.Text("File"),
    #         sg.InputText()
    #     ],
    #     [sg.Submit(key="submit"), sg.Cancel("Exit")]]