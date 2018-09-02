#include "foreach.inc" // foreach efficient loop
#include <streamer> // for streaming checkpoints
#include "playerprogress.inc" // Player Progress Bar EDIT by Southclaw http://pastebin.com/shmadNqj

#define ZONE1		0 // 0 is the done id, each time you want to add a zone just do ZONE_NAME and the zone id after it
#define ZONE2		1
#define MAX_ZONES	2 // 2 is the max number of zones, this step is obligatory

#define COLOR_RED 0xCC0000FF
#define COLOR_ORANGE 0xFFAD33FF
#define COLOR_WHITE 0x888888FF
#define COLOR_GREEN 0x00FF00FF

new tCP[MAX_ZONES]; //a variable that will show us which team is controlling a zone
new bool:UnderAttack[MAX_ZONES char ]; //a variable that will show us whether or not a zone is under attack (it returns only 2 values so we use a bool)
new CP[MAX_ZONES];  //a variable that will get a checkpoint id
new Zone[MAX_ZONES]; //a variable that will get a gang zone id
new CountVar[MAX_ZONES]; //the capture time variable
new ZUpdateTimer[MAX_ZONES]; //the repeating timer for the capture system
new bool:IsPlayerCapturing[MAX_PLAYERS][MAX_ZONES char ]; // a bool that checks the player capturing state
new bool:IsPlayerHelping[MAX_PLAYERS][MAX_ZONES char ]; // a bool that checks the player team capture assist state
new PlayerBar:ZBar; // the capture progress bar
new AttackingTeam[MAX_ZONES]; // a variable that will get the team id attacking a zone

ZoneInit()
{
	Zone[ZONE1] = GangZoneCreate(648.395, 1825.354, 813.130, 1998.494); // the capturable zone gang zone
	CP[ZONE1] = CreateDynamicCP(710.0447,1959.1855,5.5391, 4.0, -1, -1, -1, 4.0); // the czone CP 
	CreatePickup(1314, 1, 710.0447,1959.1855,5.5391, -1); // an optional pickup that has the same coordinates as the capturable zone checkpoint

	Zone[ZONE2] = GangZoneCreate(770.357910, 1575.174072, 834.357910, 1743.174072);
	CP[ZONE2] = CreateDynamicCP(801.9143,1671.0134,5.2813, 4.0, -1, -1, -1, 4.0);
	CreatePickup(1314, 1, 801.9143,1671.0134,5.2813, -1); // pickup

	for (new i = 0; i < MAX_ZONES; i++) { // looping all zones
		AttackingTeam[i] = TEAM_NOTHING; // there is no team attacking any zone at the server start,
		//which logically sets its value to TEAM_NOTHING (If you don't add this line bugs may occur)

		CountVar[i] = 25; //The zone timer in seconds (not in ms!!)
		tCP[i] = TEAM_NOTHING; // none of the zones is captured by a team,
		//which logically sets its value to TEAM_NOTHING (If you don't add this line bugs may occur)

		UnderAttack{ i } = false; // none of the zones is under attack,
		//which logically sets its value to false (If you don't add this line bugs may occur)
	}
}

ZoneInitForPlayer(playerid)
{
	// Check the progress bar include edit by southclaw (the original include doesn't have the same native [CreateProgressBar])
	ZBar = CreatePlayerProgressBar(playerid, 38.00, 435.00, 97.50, 4.19, -16776961, 25.0);

	for (new i = 0; i < MAX_ZONES; ++i) { // looping through all zones
		IsPlayerCapturing[playerid]{ i } = false; //player is not capturing on connect
		IsPlayerHelping[playerid]{ i } = false; //player is not helping on connect
		ShowZone(i); //showing the capturable zones for the player
	}
}

ZonePlayerDisconnect(playerid)
{
	for (new i = 0; i < MAX_ZONES; ++i) { // looping through all zones
		if(IsPlayerCapturing[playerid]{ i })
			LeavingZONE(playerid, i); //if the player left before finishing the capture of a zone, the zone capture will fail and call the zone leaving function
		if(IsPlayerHelping[playerid]{ i })
			IsPlayerHelping[playerid]{ i } = false; //if the player left before finishing helping capture a zone, he will be no longer helping and the variable IsPlayerHelping will be logically set to false
	}
}

ZonePlayerDeath(playerid)
{
	for (new i = 0; i < MAX_ZONES; ++i) { // looping through all zones
		if (IsPlayerCapturing[playerid]{ i }) { // if the player is capturing
		    LeavingZONE(playerid, i); // the player dies so logically he will be no longer capturing that zone. Thus, the zone leaving function is called
			if (killerid != INVALID_PLAYER_ID) { // (OPTIONAL) if the victim was capturing that zone, the killer will get extra score 
				SendClientMessage(killerid, COLOR_PINK, "[NOTICE]: You have prevented the enemy from capturing this zone, +1XP!"); //sending the bonus message to the killer
				SetPlayerScore(killerid, GetPlayerScore(killerid) +1); // setting the bonus for the killer
			}
		}
		if (IsPlayerHelping[playerid]{ i })
			IsPlayerHelping[playerid]{ i } = false; // if there player dies while helping, he will be logically no longer helping so the IsPlayerHelping variable will be set to 0
	}
}

public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	new LoopID = -1; //a new variable for an efficient CPs loop
	for (new i2 = 0; i2 < MAX_ZONES; ++i2) {
		if (checkpointid == CP[i2]) {
			LoopID = i2;
			break;
		}
	}
	if(LoopID != -1)
	{
	    if(!UnderAttack{ LoopID }) // if the zone is not under attack
	    {
			if(tCP[LoopID] != GetPlayerTeam(playerid))	ActiveZONE(playerid, LoopID); //this function starts the capture
			else
			{
				SendClientMessage(playerid, COLOR_RED,"[ERROR]: This zone is already captured by your team.");
			}
			return 1;
	    }
	    else //if the zone is under attack
	    {
		    if(AttackingTeam[LoopID] == GetPlayerTeam(playerid)) //if the player2 team is the same as the attacking team 
			{
				if(!IsPlayerCapturing[playerid]{ LoopID }) //if he is not the capturer
			    {
			        ShowPlayerProgressBar(playerid, ZBar); //show the capture progress bar for him
					SendClientMessage(playerid, COLOR_ORANGE, "[NOTICE]: You are helping your team to capture this zone.");
			        IsPlayerHelping[playerid]{ LoopID } = true; //then the player is helping
			    }
			}
		}
	}
	return 1;
}

public OnPlayerLeaveDynamicCP(playerid, checkpointid)
{
    HidePlayerProgressBar(playerid, ZBar); //hide the progress bar
    for(new i = 0; i < MAX_ZONES; ++i) //looping through possible zones
	{
		if(IsPlayerCapturing[playerid]{ i })	LeavingZONE(playerid, i); //if the player is capturing any zone this makes the capture fail
		if(IsPlayerHelping[playerid]{ i }) //makes the capture assist fail
		{
			SendClientMessage(playerid, COLOR_RED, "[FAIL]: You are no longer helping to capture this zone."); //sending the capture help fail message
			IsPlayerHelping[playerid]{ i } = false; //the player is no longer helping
		}
	}
    return 1;
}

stock ShowZone(zoneid) //the function for showing zones
{
    switch (tCP[zoneid]) //checking the team controlling a zone then applying the zone color, MAKE SURE YOU HAVE DEFINED YOUR TEAMS FIRST
    {
		case TEAM_NOTHING:	GangZoneShowForAll(Zone[zoneid], -66); //if the zone is not captured by any team (white color)
/*
	    case TEAM_AFRICA:	GangZoneShowForAll(Zone[zoneid], 0xFF9900AA);
	    case TEAM_AUSTRALIA:	GangZoneShowForAll(Zone[zoneid], 0x9400D3AA);
	    case TEAM_AMERICA:	GangZoneShowForAll(Zone[zoneid], 0x0000BBAA);
	    case TEAM_EUROPE:	GangZoneShowForAll(Zone[zoneid], 0x15FF0055);
	    case TEAM_ASIA:	GangZoneShowForAll(Zone[zoneid], 0xFF000090);
*/
		case TEAM_POLICE: GangZoneShowForAll(Zone[zoneid], TEAM_POLICE_COLOR_ZONE);
		case TEAM_REBEL: GangZoneShowForAll(Zone[zoneid], TEAM_REBEL_COLOR_ZONE);
    }
}

stock ActiveZONE(playerid, zoneid) //the function for starting the zone capture
{
    if (!UnderAttack{ zoneid }) { //if the zone is not under attack
        if (!IsPlayerInAnyVehicle(playerid)) { //if the player is not in any vehicle
			SetPlayerProgressBarValue(playerid, ZBar, 0); //setting the progress bar to its initial value
			UpdatePlayerProgressBar(playerid, ZBar); // updating the progress bar value
			AttackingTeam[zoneid] = GetPlayerTeam(playerid); // the player is attacking that zone, which means that his team is attacking it
//			switch(PlayerInfo[playerid][Vip]) // (OPTIONAL: Reducing capture timer if a player is VIP), if you want to add this, DO NOT FORGET TO ADD VIP VARIABLE
			switch (0)
            {
				case 0: //VIP level 0 for non-vip players (normal ones)
				{
					ZUpdateTimer[zoneid] = SetTimerEx("ZUpdate", 1000, 1, "di", playerid, zoneid); // 1000 (a second) * 25 (25 seconds) = 25000 milliseconds = 25 seconds (logics) is the time set for normal players to capture a zone, ZUpdateTimer[zoneid] is the timer, "d" is for the playerid capturing that zone and "i" is for establishing the zoneid
					SendClientMessage(playerid, 0xFFFFFFFF,"| Stay in this checkpoint for 25 seconds to capture this zone. |"); //sending the capture message
		    		}
				case 1: //same as the previous but now the player vip level is 1, so he gets less capture time (20 seconds) check the equation below
				{
					ZUpdateTimer[zoneid] = SetTimerEx("ZUpdate", 800, 1, "di", playerid, zoneid); // 800*25 = 20000 milliseconds = 20 seconds
					SendClientMessage(playerid, 0xFFFFFFFF,"| Stay in this checkpoint for 20 seconds to capture this zone. |");
				}
				case 2: //the more vip level is, the less time the capture takes to end, and it goes on..
				{
					ZUpdateTimer[zoneid] = SetTimerEx("ZUpdate", 600, 1, "di", playerid, zoneid); // 600*25 = 15000 milliseconds = 15 seconds
					SendClientMessage(playerid, 0xFFFFFFFF,"| Stay in this checkpoint for 15 seconds to capture this zone. |");
		    		}
				case 3: // same thing
				{
					ZUpdateTimer[zoneid] = SetTimerEx("ZUpdate", 400, 1, "di", playerid, zoneid); // 400*25 = 10000 milliseconds = 10 seconds
					SendClientMessage(playerid, 0xFFFFFFFF,"| Stay in this checkpoint for 10 seconds to capture this zone. |");
		    	}
			}
			CountVar[zoneid] = 25; //the standard count variable
            UnderAttack{ zoneid } = true; //the zone is now under attack
            IsPlayerCapturing[playerid]{ zoneid } = true; //the player is now capturing
            switch(GetPlayerTeam(playerid)) //flashing the zone according to the player team color
            {
/*
				case TEAM_AFRICA:	GangZoneFlashForAll(Zone[zoneid], 0xFF9900AA); //AGAIN DO NOT FORGET TO DEFINE YOUR TEAMS, this will flash the zone in orange color if the player is in african team
                case TEAM_AUSTRALIA:	GangZoneFlashForAll(Zone[zoneid], 0x9400D3AA);
                case TEAM_AMERICA:	GangZoneFlashForAll(Zone[zoneid], 0x0000BBAA);
				case TEAM_EUROPE:	GangZoneFlashForAll(Zone[zoneid], 0x15FF0055);
                case TEAM_ASIA:	GangZoneFlashForAll(Zone[zoneid], 0xFF000090);
*/
				case TEAM_POLICE: GangZoneFlashForAll(Zone[zoneid], TEAM_POLICE_COLOR_ZONE);
				case TEAM_REBEL: GangZoneFlashForAll(Zone[zoneid], TEAM_REBEL_COLOR_ZONE);
			}
			switch(tCP[zoneid]) //getting the team which was controlling that zone (team none is involved as well)
					{
/*
		    			case TEAM_AFRICA:	SendClientMessage(playerid, COLOR_WHITE,"This flag is controlled by {FFAF00}AFRICA"); //sending the zone previous info related to the team which was holding it to the player
		                case TEAM_AUSTRALIA:	SendClientMessage(playerid, COLOR_WHITE,"This flag is controlled by {B700FF}AUSTRALIA"); //same
		                case TEAM_AMERICA:	SendClientMessage(playerid, COLOR_WHITE,"This flag is controlled by {0049FF}AMERICA"); //same
						case TEAM_EUROPE:	SendClientMessage(playerid, COLOR_WHITE,"This flag is controlled by {6EF83C}EUROPE"); //same
		                case TEAM_ASIA:	SendClientMessage(playerid, COLOR_WHITE,"This flag is controlled by {F81414}ASIA"); // same
		                case TEAM_NOTHING:	SendClientMessage(playerid, COLOR_WHITE,"This flag is not controlled by any team!"); // same
*/
						case TEAM_POLICE: SendClientMessage(playerid, COLOR_WHITE,"This flag is controlled by Police");
						case TEAM_REBEL: SendClientMessage(playerid, COLOR_WHITE,"This flag is controlled by Rebel");
						}	        
        }else return SendClientMessage(playerid, COLOR_RED,"[ERROR]: You cannot capture while in a vehicle!"); //let's get back to IsPlayerInAnyVehicle, if it is true, then the player gets this message and he can't capture
    }else return SendClientMessage(playerid, COLOR_RED,"[WARNING]: This zone is already being taken over!"); //let's get back to UnderAttack[zoneid], if it is true, then the player gets this message and he can't capture
    return 1;
}

stock ZONECaptured(playerid, zoneid) //the function that results after a zone is a successfully captured
{
// when the zone is captures -->
	UnderAttack{ zoneid } = false; // it is no longer under attack
	KillTimer(ZUpdateTimer[zoneid]); // the capture timer ends
	SetPlayerScore(playerid, GetPlayerScore(playerid)+5); //the player gets score (5 here in this example)
	GivePlayerMoney(playerid, 1000); // the player gets some pennies $$
	new strr[200]; // a new variable you will use later for sending success message
	format(strr, sizeof(strr), "[SUCCESS]: You have captured %s! You received +5XP & +$1000.", ZName(zoneid)); //formatting the success message : %s refers to the zone name identified by ZName(zoneid) (check this function in the other part of my tutorial)
	SendClientMessage(playerid, COLOR_GREEN, strr); // sending the success message
	IsPlayerCapturing[playerid]{ zoneid } = false; //the player "playerid" is no longer capturing the zone "zoneid" and the reason for which I used { } for zoneid is new bool:IsPlayerCapturing[MAX_PLAYERS][MAX_ZONES char ] that I used char for MAX_ZONES to optimize the code, check its explanation on samp forums!
	AttackingTeam[zoneid] = TEAM_NOTHING; // there is no team attacking that zone
	//==========================================================================
    foreach (new i : Player) // looping through all players
	{
		// looping through the players which are in the team that lost the zone
		// (but the zone is now captured by another team!
		// why tCP[zoneid] == GetPlayerTeam(i) ??) : simply because I did
		// not set tCP[zoneid] for the new team, it is still set for the old one and will be set just after this part
	    if (tCP[zoneid] == GetPlayerTeam(i)) {
			SetPlayerScore(i, GetPlayerScore(i)-1); // giving -1 score for the team which lost that zone
			new str[110]; //creating a new string for a client message
			format( str, sizeof(str), "[NOTICE]: Your team has lost {FFAF00}%s, {F81414}-1XP", ZName(zoneid)); // ZName Already explained; formatting the zone loss message for the team which lost that zone  
			SendClientMessage(i, 0xFFFFFFFF, str); // sending the message
		}
		// looping through the players which are in the same team as the player who captured the zone
		if (GetPlayerTeam(i) == GetPlayerTeam(playerid)) {
		    SetPlayerScore(i, GetPlayerScore(i)+1); //giving all of them 1 score
			// making sure that that any player from the same team does not have the
			// same id as the one who captured it so that he doesn't get the capture success message twice!
			if (i != playerid) {
				new str[110]; //creating a new string
				format( str, sizeof(str), "[NOTICE]: Your team has captured {FFAF00}%s, {6EF83C}+1XP", ZName(zoneid)); // Already explained
				SendClientMessage(i, COLOR_GREEN, str); //sending the notice to the rest of the team mates
			}
		}
		if (IsPlayerHelping[i]{ zoneid }) //looping through the player(s) who helped in the capture
		{
		    SendClientMessage(i, COLOR_GREEN,"[NOTICE]: You have helped capturing this area! You received +3 XP for it!"); //sending him/them the capture success message
			SetPlayerScore(i, GetPlayerScore(i)+3); //setting his/their score to [score]+3
			IsPlayerHelping[i]{ zoneid } = false; // he/they is/are not helping capturing the zone anymore
			HidePlayerProgressBar(i, ZBar); //hiding the capture bar (progress bar) as the capture has finished 
		}
	}
    //==========================================================================
    tCP[zoneid] = GetPlayerTeam(playerid); //the zone is now controlled by the new team! Then logically  tCP[zoneid] will be set for the new team which will be gotten by getting the player -who captured that zone- team (GetPlayerTeam(playerid))
    GangZoneStopFlashForAll(Zone[zoneid]); //stopping the zone from getting flashed
    //==========================================================================
    switch(GetPlayerTeam(playerid)) //setting the new color defined by the new team for that zone (AGAIN AND AGAIN DO NOT FORGET TO DEFINE YOUR TEAMS)
	{
/*
		case TEAM_AFRICA:	GangZoneShowForAll(Zone[zoneid], 0xFF9900AA);
        case TEAM_AUSTRALIA:	GangZoneShowForAll(Zone[zoneid], 0x9400D3AA);
        case TEAM_AMERICA:	GangZoneShowForAll(Zone[zoneid], 0x0000BBAA);
        case TEAM_EUROPE:	GangZoneShowForAll(Zone[zoneid], 0x15FF0055);
        case TEAM_ASIA:	GangZoneShowForAll(Zone[zoneid], 0xFF000090);
*/
		case TEAM_POLICE: GangZoneShowForAll(Zone[zoneid], TEAM_POLICE_COLOR_ZONE);
		case TEAM_REBEL: GangZoneShowForAll(Zone[zoneid], TEAM_REBEL_COLOR_ZONE);
	}
	HidePlayerProgressBar(playerid, ZBar); // Hiding the capture bar for the player who finished capturing
    return 1;
}

stock ZName(zoneidd) // a function which will return the zone name
{
	new zname[24]; // a new string for returning the zone name
    switch(zoneidd) // switching between the several zones ids in order to get the right one
    {
        case ZONE1:	zname = "Zone 1"; // example, if the zone id is 1 (ZONE1), then it's name must be "Zone 1"!
        case ZONE2:	zname = "Zone 2"; // same thing
        //.....
	}
	return zname; //returning the zone name string
}

stock LeavingZONE(playerid, zoneid)
{
// If the player left the zone before finishing the capture no matter what the reason was = the capture fails, therefore -->
	HidePlayerProgressBar(playerid, ZBar); // the progress bar for the capture will be hidden
	AttackingTeam[zoneid] = TEAM_NOTHING; //Zone is not attacked by any team
	UnderAttack{ zoneid } = false; // The zone is no longer under attack
	KillTimer(ZUpdateTimer[zoneid]); //Killing the capture timer
	IsPlayerCapturing[playerid]{ zoneid } = false; //the player "playerid" is no longer attacking that zone "zoneid"
	CountVar[zoneid] = 25; //setting back the zone capture time standard value (25 seconds)
	foreach (new i : Player) //looping through all players to get the ones who were helping : They will be no longer helping (if they were)
	{
		if(IsPlayerHelping[i]{ zoneid }) //if the player was helping capturing that zone
		{
			IsPlayerHelping[i]{ zoneid } = false; //he will be no longer helping
			HidePlayerProgressBar(i, ZBar); //and the progress bar will be hidden for him
		}
	}
    GangZoneStopFlashForAll(Zone[zoneid]); //the zone stops from flashing as the capture failed and ended
	SendClientMessage(playerid, COLOR_RED,"[FAIL]: You have failed to capture this zone."); // the fail message is sent
    return 1;
}

forward ZUpdate(playerid, zoneid); //the timer for the zone capture system
public ZUpdate(playerid, zoneid) // it has to be public because it is a TIMER, orelse it won't work
{
	if(CountVar[zoneid] > 0) //if the zone is still being captured (then logically the remaining time will be > 0 seconds right?)
	{
		CountVar[zoneid] --; // continue on decreasing the capture time by 1 second (1 second on each cycle of course)
		SetPlayerProgressBarValue(playerid, ZBar, 25 - CountVar[zoneid]); //increasing the progress bar value (25 - [a number that is descreasing under 25] = will become more and more higher right? till it become 25!
		UpdatePlayerProgressBar(playerid, ZBar); //updating the progress bar value
		foreach (new i : Player) // looping through all players
		{
			if(IsPlayerHelping[i]{ zoneid } == true) //if the player is helping
			{
			    SetPlayerProgressBarValue(i, ZBar, 25 - CountVar[zoneid]); //setting the progress bar value for him (same logics as I explained in the previous lines)
				UpdatePlayerProgressBar(i, ZBar); // updating the progress bar value
	            CountVar[zoneid] --; //haha, here comes the smartest part of the script, which I like the most, we said that the more players capturing a zone the less time its capture takes right? then as you can see for each helping player an extra 1 second will be taken from the capture time!!!!!
			}
		}
	}
	else if(CountVar[zoneid] == 0) // if the remaining capture time = 0, then the capture ended right?
	{
		ZONECaptured(playerid, zoneid); // the zone is captured, calling the function reserved for that!
		HidePlayerProgressBar(playerid, ZBar); // hiding the progress bar
		KillTimer(ZUpdateTimer[zoneid]); // killing the capture timer for that zone
		CountVar[zoneid] = 25; // resetting the capture time back to 25 seconds
	} //but this is not enough, sometimes, the Count Variable which indicates the remaining time (CountVar) can become negative for reasons I don't have time to explain here, so we have to check that too in order to avoid bugs!! (trust me it's tested and it's an obligatory check)
	else if(CountVar[zoneid] < 0) // if the remaining time went under 0 (became negative) then the zone must be captured, right?
	{
		ZONECaptured(playerid, zoneid);  //same thing will be applied
		HidePlayerProgressBar(playerid, ZBar); // same thing will be applied
		KillTimer(ZUpdateTimer[zoneid]); //same thing will be applied
		CountVar[zoneid] = 25; // same thing will be applied
	}
    return 1;
}