#define DEFAULT_COLOR A9C4E4

enum
{
	DIALOG_LOGIN,
	DIALOG_HELP,
	DIALOG_HELP_INFO,
	DIALOG_HELP_CMDS
}

new dialog_serverInfo[] =
"Gamemode writing since {70B8FF}25 January 2015{A9C4E4}\n\n\
lanmode 1\n\
onfoot_rate 20\n\
incar_rate 20\n\
weapon_rate 20\n\
stream_distance 500.0\n\
stream_rate 1000";

EQ_DialogInit()
{
	
}

EQ_HelpBox(playerid)
{
	ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "Help", "Commands\nServer Information", "Open", "Close");
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == DIALOG_HELP)
		if (response == 1)
			switch (listitem) {
				case 0:
					ShowPlayerDialog(playerid, DIALOG_HELP_CMDS, DIALOG_STYLE_MSGBOX, "Commands", "!<text>\tTeam chat\n/kill\n/ep", "Back", "");
				case 1:
					ShowPlayerDialog(playerid, DIALOG_HELP_INFO, DIALOG_STYLE_MSGBOX, "Server Information", dialog_serverInfo, "Back", "");
			}
	if (dialogid == DIALOG_HELP_INFO || dialogid == DIALOG_HELP_CMDS)
		EQ_HelpBox(playerid);
}