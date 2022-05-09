#include "findFrame.h"
//findFrame J:\input\video\GMT20210331-114231_Recording_avo_640x360.mp4  
//			J:\input\video\fixation_resized.png 
//			J:\input\video\ image_times.txt  
//			J:\input\video\GMT20210331-114231_Recording_gvo_1280x720.mp4 
//			-600 
//			1
using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

#define ARGID_REFVID 'r'
#define ARGID_REFVID_IDX 0
#define ARGID_REFVIMG 'i'
#define ARGID_REFVIMG_IDX (ARGID_REFVID_IDX + 1)
#define ARGID_FOCVID 'f'
#define ARGID_FOCVID_IDX (ARGID_REFVIMG_IDX + 1)
#define ARGID_TIMELIST 'l'
#define ARGID_TIMELIST_IDX (ARGID_FOCVID_IDX + 1) 
#define ARGID_TIMEREF 't'
#define ARGID_TIMEREF_IDX (ARGID_TIMELIST_IDX + 1)
#define ARGID_SEARCHTIME 's'
#define ARGID_SEARCHTIME_IDX (ARGID_TIMEREF_IDX + 1)
#define ARGID_DESTDIR 'd'
#define ARGID_DESTDIR_IDX (ARGID_SEARCHTIME_IDX + 1)
#define ARGID_TRIGCOUNT 'c'
#define ARGID_TRIGCOUNT_IDX (ARGID_DESTDIR_IDX + 1)
#define ARGID_AUTORUN 'a'
#define ARGID_AUTORUN_IDX (ARGID_TRIGCOUNT_IDX + 1)
#define MAX_ARG (ARGID_AUTORUN_IDX + 1)


	bool parseSwitchForm = false;
	VideoProc::MainForm form;
	// video, start time, end time
	// bright contrast
	if (args[0][0] == '-') {
		parseSwitchForm = true;
		int argsIdx[MAX_ARG];
		String^ emptyArg = gcnew String("");
		for (int argidx = 0; argidx < MAX_ARG; argidx++) {
			argsIdx[argidx] = -1;
		}
		for (int argidx = 0; argidx < args->Length; argidx++) {
			if (args[argidx][0] == '-') {
				switch (args[argidx][1]) {
				case ARGID_REFVID:
					argsIdx[ARGID_REFVID_IDX] = argidx;
					break;
				case ARGID_FOCVID:
					argsIdx[ARGID_FOCVID_IDX] = argidx;
					break;
				case ARGID_TIMELIST:
					argsIdx[ARGID_TIMELIST_IDX] = argidx;
					break;
				case ARGID_TIMEREF:
					argsIdx[ARGID_TIMEREF_IDX] = argidx;
					break;
				case ARGID_SEARCHTIME:
					argsIdx[ARGID_SEARCHTIME_IDX] = argidx;
					break;
				case ARGID_DESTDIR:
					argsIdx[ARGID_DESTDIR_IDX] = argidx;
					break;
				case ARGID_TRIGCOUNT:
					argsIdx[ARGID_TRIGCOUNT_IDX] = argidx;
					break;
				case ARGID_AUTORUN:
					argsIdx[ARGID_AUTORUN_IDX] = argidx;
					break;
				}
			}
		}
		String ^tmp = (argsIdx[ARGID_REFVID_IDX] < 0) ? emptyArg : args[argsIdx[ARGID_REFVID_IDX]]->Substring(2);
		tmp = (argsIdx[ARGID_REFVIMG_IDX] < 0) ? emptyArg : args[argsIdx[ARGID_REFVIMG_IDX]]->Substring(2);
		tmp = (argsIdx[ARGID_TIMELIST_IDX] < 0) ? emptyArg : args[argsIdx[ARGID_TIMELIST_IDX]]->Substring(2);
		tmp = (argsIdx[ARGID_FOCVID_IDX] < 0) ? emptyArg : args[argsIdx[ARGID_FOCVID_IDX]]->Substring(2);
		tmp = (argsIdx[ARGID_TIMEREF_IDX] < 0) ? emptyArg : args[argsIdx[ARGID_TIMEREF_IDX]]->Substring(2);
		tmp = (argsIdx[ARGID_SEARCHTIME_IDX] < 0)? emptyArg : args[argsIdx[ARGID_SEARCHTIME_IDX]]->Substring(2);
		tmp = (argsIdx[ARGID_DESTDIR_IDX] < 0)? emptyArg : args[argsIdx[ARGID_DESTDIR_IDX]]->Substring(2);
		tmp = (argsIdx[ARGID_TRIGCOUNT_IDX] < 0)? emptyArg : args[argsIdx[ARGID_TRIGCOUNT_IDX]]->Substring(2);
		form.autoRunStr(
			(argsIdx[ARGID_REFVID_IDX] < 0) ? emptyArg : args[argsIdx[ARGID_REFVID_IDX]]->Substring(2),
			(argsIdx[ARGID_REFVIMG_IDX] < 0) ? emptyArg : args[argsIdx[ARGID_REFVIMG_IDX]]->Substring(2),
			(argsIdx[ARGID_TIMELIST_IDX] < 0) ? emptyArg : args[argsIdx[ARGID_TIMELIST_IDX]]->Substring(2),
			(argsIdx[ARGID_FOCVID_IDX] < 0) ? emptyArg : args[argsIdx[ARGID_FOCVID_IDX]]->Substring(2),
			(argsIdx[ARGID_TIMEREF_IDX] < 0) ? emptyArg : args[argsIdx[ARGID_TIMEREF_IDX]]->Substring(2),
			argsIdx[ARGID_TIMEREF_IDX] >= 0,
			(argsIdx[ARGID_SEARCHTIME_IDX] < 0)? emptyArg : args[argsIdx[ARGID_SEARCHTIME_IDX]]->Substring(2),
			(argsIdx[ARGID_DESTDIR_IDX] < 0)? emptyArg : args[argsIdx[ARGID_DESTDIR_IDX]]->Substring(2),
			(argsIdx[ARGID_TRIGCOUNT_IDX] < 0)? emptyArg : args[argsIdx[ARGID_TRIGCOUNT_IDX]]->Substring(2),
			(argsIdx[ARGID_AUTORUN_IDX] < 0) ? true : args[argsIdx[ARGID_AUTORUN_IDX]][2] != 'N');
	}
	else {
		// leave these here to maintain the previous form of CLI
		if (args->Length == 3) {
			form.autoRun(args[0], args[1], args[2]);
		}
		if (args->Length == 4) {
			form.autoRun(args[0], args[1], args[2], args[3]);
		}
		if (args->Length == 5) {
			form.autoRun(args[0], args[1], args[2], args[3], args[4]);
		}
		if (args->Length == 6) {
			form.autoRun(args[0], args[1], args[2], args[3], args[4], args[5]);
		}
	}


	Application::Run(%form);
}


