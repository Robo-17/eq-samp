#include <a_samp>

#include "secure.inc"
#include "res.inc"
#include "dialog.inc"

//#define MAX_PING_COUNT 5

#define MAX_CMD 64
#define MAX_CMDS 3

#undef MAX_PLAYERS
//#undef MAX_VEHICLES
#define MAX_PLAYERS 30
//#define MAX_VEHICLES 100

#define ResetMoneyBar ResetPlayerMoney
#define UpdateMoneyBar GivePlayerMoney

enum
{
	TEAM_NOTHING,
	TEAM_NPC,
	TEAM_POLICE,
	TEAM_REBEL
}

#define TEAM_POLICE_COLOR 0x0066FF66
#define TEAM_POLICE_COLOR_CHAT 0x00AAFFFF
#define TEAM_POLICE_COLOR_ZONE 0x00AAFF55
#define TEAM_REBEL_COLOR 0xFF990066
#define TEAM_REBEL_COLOR_CHAT 0xFFCC66FF
#define TEAM_REBEL_COLOR_ZONE 0xFFCC6655

#include "zone.inc"

new veh, veh_hydra;
new mod1, mod2, mod3;
new worldTime = 3, weatherRunning, weatherCount, weatherID;

new Float:npc_x = -1546.130;
new Float:npc_y = 317.000;
new Float:npc_z = 54.500;

//new pPingCount[MAX_PLAYERS][MAX_PING_COUNT];
//new pPingPointer[MAX_PLAYERS];
new pName[MAX_PLAYERS][MAX_PLAYER_NAME];
new pMoney[MAX_PLAYERS];
new bool:pBeingProtected[MAX_PLAYERS];
new bool:pFirstSpawn[MAX_PLAYERS];

EQ_ClearPlayerData(playerid)
{
	pMoney[playerid] = 0;
}

EQ_GivePlayerCash(playerid, money)
{
	pMoney[playerid] += money;
	ResetMoneyBar(playerid);//Resets the money in the original moneybar, Do not remove!
	UpdateMoneyBar(playerid, pMoney[playerid]);//Sets the money in the moneybar to the serverside cash, Do not remove!
	return pMoney[playerid];
}

EQ_SetPlayerCash(playerid, money)
{
	pMoney[playerid] = money;
	ResetMoneyBar(playerid);//Resets the money in the original moneybar, Do not remove!
	UpdateMoneyBar(playerid, pMoney[playerid]);//Sets the money in the moneybar to the serverside cash, Do not remove!
	return pMoney[playerid];
}

EQ_ResetPlayerCash(playerid)
{
	pMoney[playerid] = 0;
	ResetMoneyBar(playerid);//Resets the money in the original moneybar, Do not remove!
	UpdateMoneyBar(playerid, pMoney[playerid]);//Sets the money in the moneybar to the serverside cash, Do not remove!
	return pMoney[playerid];
}

EQ_GetPlayerCash(playerid)
{
	return pMoney[playerid];
}
/*
public MoneyTimer()
{
	new username[MAX_PLAYER_NAME];
	for (new i=0; i<MAX_PLAYERS; i++) {
		if (IsPlayerConnected(i)) {
			if (GetPlayerCash(i) != GetPlayerMoney(i)) {
				ResetMoneyBar(i); //Resets the money in the original moneybar, Do not remove!
				UpdateMoneyBar(i, GetPlayerCash(i)); //Sets the money in the moneybar to the serverside cash, Do not remove!
				new hack = GetPlayerMoney(i) - GetPlayerCash(i);
				GetPlayerName(i, username, sizeof(username));
				printf("%s has picked up/attempted to spawn $%d.", username, hack);
			}
		}
	}
}
*/

new weatherCycle[] = {20, 8, 20, 0};

new Float:randomSpawnPolice[][4] =
{
    {-1754.200,956.6630,24.880,180.000},
    {-1730.700,957.880,24.880,90.000},
    {-1711.450,999.070,17.914,90.000},
	{-1717.760,1043.770,17.914,180.000}
};
new Float:randomSpawnRebel[][4] =
{
	{-2071.850,306.7260,41.990,180.000},
	{-2131.450,262.730,35.780,270.000},
	{-2126.700,239.290,37.370,268.100},
	{-2131.536,167.560,35.290,268.900}
};

new chatForbid[][8] =
{
	"rcon",
	"login",
	0
};

new serverWeapons[] =
{
	0, // Fist
	WEAPON_NITESTICK,
	WEAPON_BAT,
	WEAPON_MP5,
	WEAPON_TEC9,
	WEAPON_RIFLE,
//	WEAPON_SNIPER,
	WEAPON_PARACHUTE,
	WEAPON_VEHICLE,
	50, // Helicopter blades
	51, // Explosion
	WEAPON_DROWN,
	WEAPON_COLLISION,
	-1 // End list
};

main(){}

forward EQ_WorldTimeSys();
forward EQ_WeatherSys();
forward EQ_EndAntiSK(playerid);

EQ_RocketExplosion(Float:x, Float:y, Float:z)
{
	CreateExplosion(x, y, z+26.0, 11, 5.0);
	CreateExplosion(x, y, z+18.0, 11, 5.0);
	CreateExplosion(x, y, z+11.0, 11, 5.0);
	CreateExplosion(x, y, z+5.0, 11, 5.0);
	CreateExplosion(x, y, z+5.0, 1, 5.0);
	CreateExplosion(x, y, z-5.0, 7, 10.0);
}

EQ_PlayerWorldLimit()
{
	new Float:playerX, Float:playerY, Float:playerZ;
	for (new i = 0; i < MAX_PLAYERS; i++) {
		if (!IsPlayerConnected(i))
			return;
		GetPlayerPos(i, playerX, playerY, playerZ);
		if (playerX > -970.0 || playerY > 1600.0 || playerY < -808.0) {
			SendClientMessage(i, 0xFF9999FF, "Out of warzone");
			GetPlayerPos(i, playerX, playerY, playerZ); // If lag
			EQ_RocketExplosion(playerX, playerY, playerZ);
		}
	}
}

public EQ_WorldTimeSys()
{
	if (worldTime == 23)
		worldTime = 0;
	else
		++worldTime;
	if (!weatherRunning && (worldTime%6 == 0 || worldTime == 0) && (random(10) == 9)) {
		weatherRunning = 1;
		EQ_WeatherSys();
	}
	SetWorldTime(worldTime);

	EQ_PlayerWorldLimit();
}

public EQ_WeatherSys()
{
	if (weatherCycle[weatherCount] != 0) {
		SetWeather(weatherCycle[weatherCount++]);
		SetTimer("EQ_WeatherSys", 30000, false);
	} else {
		SetWeather(7);
		weatherRunning = 0;
		weatherCount = 0;
	}
}

EQ_ErrorMsg(playerid, text[])
{
	GameTextForPlayer(playerid, text, 1500, 4);
}

EQ_RespawnVehicles()
{
	for (new i = 2; i <= MAX_VEHICLES; i++) {
		SetVehicleToRespawn(i);
	}
}

public OnGameModeInit()
{
	SetGameModeText("TheFuture");
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
	ShowNameTags(1);
	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	SetWeather(7);
	UsePlayerPedAnims();

	SetWorldTime(worldTime);
	SetTimer("EQ_WorldTimeSys", 30000, true);

	AddPlayerClassEx(TEAM_POLICE,285,-1754.200,956.663,24.880,180.000,0,0,0,0,0,0);
	AddPlayerClassEx(TEAM_REBEL,16,-2071.850,306.726,41.990,180.000,0,0,0,0,0,0);

	// NPC
	veh_hydra = AddStaticVehicle(520,npc_x,npc_y,npc_z,0.000,1,1);
	// Modded
	mod1 = AddStaticVehicleEx(561,-1981.683,952.228,45.270,180.000,1,1,VEH_DELAY);
	mod2 = AddStaticVehicleEx(483,-2093.150,87.112,35.315,0.000,1,1,VEH_DELAY);
	mod3 = AddStaticVehicleEx(534,-2129.952,765.636,69.296,180.000,1,1,VEH_DELAY);

	EQ_AddVehicles();
	EQ_RespawnVehicles(); // Apply custom health
	EQ_AddObjects();

	EQ_DialogInit();

	ZoneInit();

	ConnectNPC("NPC", "air");
}

public OnVehicleSpawn(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
		case 586, 471:
			SetVehicleHealth(vehicleid, 750.0);
		case 516, 609:
			SetVehicleHealth(vehicleid, 2000.0);
		case 482, 413, 573:
			SetVehicleHealth(vehicleid, 1500.0);
		case 583:
			SetVehicleHealth(vehicleid, 650.0);
		case 485, 574:
			SetVehicleHealth(vehicleid, 700.0);
	}
	if (vehicleid == mod1) {
/*
		AddVehicleComponent(vehicleid, 1057);
		AddVehicleComponent(vehicleid, 1059);
		AddVehicleComponent(vehicleid, 1063);
		AddVehicleComponent(vehicleid, 1156);
		AddVehicleComponent(vehicleid, 1157);
*/
		ChangeVehiclePaintjob(vehicleid, 2);
		return;
	}
	if (vehicleid == mod2) {
		ChangeVehiclePaintjob(vehicleid, 0);
		return;
	}
	if (vehicleid == mod3) {
/*
		AddVehicleComponent(vehicleid, 1106);
		AddVehicleComponent(vehicleid, 1124);
		AddVehicleComponent(vehicleid, 1125);
		AddVehicleComponent(vehicleid, 1126);
		AddVehicleComponent(vehicleid, 1178);
		AddVehicleComponent(vehicleid, 1179);
*/
		ChangeVehiclePaintjob(vehicleid, 2);
		return;
	}
}

EQ_FlipPlayer(playerid)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	SetPlayerPos(playerid, x, y, z);
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	switch (GetVehicleModel(vehicleid)) {
		case 516, 598, 609:
			if (GetPlayerTeam(playerid) != TEAM_POLICE) {
				EQ_FlipPlayer(playerid);
				//GameTextForPlayer(playerid, "Police only", 500, 3);
			}
		case 404, 566:
			if (GetPlayerTeam(playerid) != TEAM_REBEL) {
				EQ_FlipPlayer(playerid);
				//GameTextForPlayer(playerid, "Rebel only", 500, 3);
			}
	}
}
new a[16];
public OnVehicleMod(playerid, vehicleid, componentid)
{
	format(a, sizeof(a), "* Mod %d", componentid);
	if (GetPlayerInterior(playerid) == 0) {
		if (IsPlayerAdmin(playerid)) {
			SendClientMessageToAll(0x00FF00FF, a);
			return 1;
		}
		EQ_BanPlayer(playerid, "AUTO: Vehicle mod");
		return 0;
	}
	SendClientMessageToAll(0x00FF00FF, a);
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	format(a, sizeof(a), "* Paintjob %d", paintjobid);
	if (GetPlayerInterior(playerid) == 0) {
		if (IsPlayerAdmin(playerid)) {
			SendClientMessageToAll(0x00FF00FF, a);
			return 1;
		}
		EQ_BanPlayer(playerid, "AUTO: Vehicle paintjob");
		return 0;
	}
	SendClientMessageToAll(0x00FF00FF, a);
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if (!IsPlayerConnected(playerid))
		return 0;
	if (IsPlayerInAnyVehicle(playerid))
		SetPlayerArmedWeapon(playerid, 0);
	return 1;
}

EQ_ConnectMsg(playerid, reason)
{
	new joinMsg[MAX_PLAYER_NAME + 16] = "> %s: %s";
	new join[] = "Join", quit[] = "Quit", timeout[] = "Timeout";

	switch (reason) {
		case 0:
			format(joinMsg, sizeof(joinMsg), joinMsg, timeout, pName[playerid]);
		case 1, 2:
			format(joinMsg, sizeof(joinMsg), joinMsg, quit, pName[playerid]);
		case 3:
			format(joinMsg, sizeof(joinMsg), joinMsg, join, pName[playerid]);
	}
	SendClientMessageToAll(0x888888FF, joinMsg);
}

public OnPlayerDisconnect(playerid, reason)
{
	ZonePlayerDisconnect(playerid);
	EQ_ConnectMsg(playerid, reason);

	EQ_ClearPlayerData(playerid);
}

public OnPlayerConnect(playerid)
{
	new connIP[16];
	GetPlayerName(playerid, pName[playerid], MAX_PLAYER_NAME);
	GetPlayerIp(playerid, connIP, 16);

	if (strcmp(connIP, "127.0.0.1", true) == 0) {
		if (IsPlayerNPC(playerid))
			return 0;
	} else if (EQ_SecureCheck(playerid, connIP) == 0)
		return 0;

	EQ_ConnectMsg(playerid, 3);

	EQ_RemoveBuildings(playerid);

	SetPlayerMapIcon(playerid, 0, -1745.550,964.126,24.900, 30, 0, MAPICON_GLOBAL);
	SetPlayerMapIcon(playerid, 1, -2062.173,211.716,35.664, 20, 0, MAPICON_GLOBAL);

	ZoneInitForPlayer(playerid);

	EQ_ResetPlayerCash(playerid);
	EQ_SetPlayerCash(playerid, 5000);
	pFirstSpawn[playerid] = true;

	return 0;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerCameraPos(playerid, -1932.633,554.484,205.283);
	SetPlayerCameraLookAt(playerid, -1928.633,559.484,202.283);
	SetPlayerPos(playerid, -1928.633,559.484,202.283);
	SetPlayerFacingAngle(playerid, 135.000);
	if (GetPlayerTeam(playerid) == TEAM_POLICE) {
		GameTextForPlayer(playerid, "Police", 1000, 6);
		SetPlayerColor(playerid, TEAM_POLICE_COLOR);
	} else {
		GameTextForPlayer(playerid, "~y~Rebel", 1000, 6);
		SetPlayerColor(playerid, TEAM_REBEL_COLOR);
	}

	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (!IsPlayerNPC(playerid) && newstate == PLAYER_STATE_DRIVER) {
		if (GetPlayerVehicleID(playerid) == veh_hydra)
			EQ_BanPlayer(playerid, "AUTO: NPC vehicle seat");
	}
}

public EQ_EndAntiSK(playerid)
{
	SetPlayerHealth(playerid, 100);
	SetPlayerArmour(playerid, 50);
	pBeingProtected[playerid] = false;
}

EQ_AntiSK(playerid)
{
	SetPlayerHealth(playerid, 99000);
	pBeingProtected[playerid] = true;
	SetTimerEx("EQ_EndAntiSK", 10000, false, "i", playerid);
}

public OnPlayerSpawn(playerid)
{
	new rand;

	if (IsPlayerNPC(playerid)) {
		SetSpawnInfo(playerid, TEAM_NPC, 217, npc_x, npc_y, npc_z, 0, 0, 0, 0, 0, 0, 0);
		SetPlayerTeam(playerid, TEAM_NPC);
		SetPlayerColor(playerid, 0xFF000000);
		SetPlayerSkin(playerid, 217);
		PutPlayerInVehicle(playerid, veh_hydra, 0);
		return 1;
	}
/*
	if (!IsPlayerAdmin(playerid))
		SetPlayerWorldBounds(playerid, -1230.000, -2290.000, 1600.000, -693.000);
	else
		SetPlayerWorldBounds(playerid, 20000.0000, -20000.0000, 20000.0000, -20000.0000);
*/
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 998);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 998);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 999);

	if (IsPlayerAdmin(playerid)) {
		GivePlayerWeapon(playerid, WEAPON_MINIGUN, 10000);
		EQ_SetPlayerCash(playerid, 50000);
	}

	if (GetPlayerTeam(playerid) == TEAM_POLICE) {
		GivePlayerWeapon(playerid, WEAPON_NITESTICK, 1);
		GivePlayerWeapon(playerid, WEAPON_MP5, 230);
		GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 100);
		rand = random(sizeof(randomSpawnPolice));
		SetPlayerPos(playerid, randomSpawnPolice[rand][0], randomSpawnPolice[rand][1],randomSpawnPolice[rand][2]);
		SetPlayerFacingAngle(playerid, randomSpawnPolice[rand][3]);
		SetCameraBehindPlayer(playerid);
		switch (random(3)) {
			case 0: SetPlayerSkin(playerid, 285);
			case 1: SetPlayerSkin(playerid, 71);
		}
	} else {
		GivePlayerWeapon(playerid, WEAPON_BAT, 1);
		GivePlayerWeapon(playerid, WEAPON_TEC9, 250);
		GivePlayerWeapon(playerid, WEAPON_RIFLE, 75);
		rand = random(sizeof(randomSpawnRebel));
		SetPlayerPos(playerid, randomSpawnRebel[rand][0], randomSpawnRebel[rand][1],randomSpawnRebel[rand][2]);
		SetPlayerFacingAngle(playerid, randomSpawnRebel[rand][3]);
		SetCameraBehindPlayer(playerid);
		switch (random(3)) {
			case 0: SetPlayerSkin(playerid, 16);
			case 1: SetPlayerSkin(playerid, 50);
			case 2: SetPlayerSkin(playerid, 261);
		}
	}

	EQ_AntiSK(playerid);

	if (!pFirstSpawn[playerid])
		EQ_SetPlayerCash(playerid, pMoney[playerid]);
	else
		EQ_HelpBox(playerid);

	return 1;
}

public OnPlayerText(playerid, text[])
{
    new pText[150+MAX_PLAYER_NAME];
	new bool:team;
	new d, t;

	t = GetPlayerTeam(playerid);
	while (chatForbid[d][0]) {
		if (strfind(text, chatForbid[d++], true) != -1) {
			SendClientMessage(playerid, 0xCC0000FF, "* Forbidden words!");
			return 0;
		}
	}

	if (text[0] == '!') {
		text[0] = ' ';
		team = true;
	}
	SetPlayerChatBubble(playerid, text, 0x66FF99FF, 70.0, 5000);
	format(pText, sizeof(pText), "%d : %s: %s", playerid, pName[playerid], text);

	if (team) {
		for (new i = 0; i < MAX_PLAYERS; i++) {
			if (IsPlayerConnected(i) && GetPlayerTeam(i) == t) {
				SendClientMessage(i, 0x66FF99FF, pText);
			}
		}
		return 0;
	}

	SendClientMessageToAll(t == TEAM_POLICE ? TEAM_POLICE_COLOR_CHAT : TEAM_REBEL_COLOR_CHAT, pText);

	return 0;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	GameTextForPlayer(playerid, "~r~Wasted", 3000, 0);
	if (pFirstSpawn[playerid])
		pFirstSpawn[playerid] = false;

	if (IsPlayerConnected(killerid)) {
		if (!IsPlayerAdmin(killerid)) {
			new i;
			while (serverWeapons[i] != -1)
				if (reason == serverWeapons[i++])
					return;
			EQ_BanPlayer(killerid, "AUTO: Illegal weapon");
		}
		if (pBeingProtected[playerid] == true)
			Kick(killerid);
	}
}

EQ_HandlePlayerCommand(cmdtext[], cmds[][])
{
	new str, stlb, i;
	while (cmdtext[i] != '\0') {
		if (cmdtext[i] != ' ')
			cmds[str][stlb++] = cmdtext[i++];
		else if (i > MAX_CMD-1 || str > MAX_CMDS-1)
			return;
		else {
			++i;
			++str;
			stlb = 0;
		}
	}
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	new cmds[MAX_CMDS][MAX_CMD];
	new cmd2n, cmd3n;
	EQ_HandlePlayerCommand(cmdtext, cmds);
	cmd2n = strval(cmds[1]); cmd3n = strval(cmds[2]);

	if (IsPlayerAdmin(playerid)) {
		if (strcmp(cmds[0], "/v", true) == 0) {
			new Float:x, Float:y, Float:z;
			new Float:vz;
			if (cmd2n < 400 || cmd2n > 611) {
				GameTextForPlayer(playerid, "~g~400~p~ - ~g~611", 2000, 3);
				return 1;
			}
			GetPlayerPos(playerid, x, y, z);
			if (IsPlayerInAnyVehicle(playerid)) {
				GetVehicleZAngle(veh, vz);
			} else
				GetPlayerFacingAngle(playerid, vz);
			DestroyVehicle(veh);
			veh = CreateVehicle(cmd2n, x, y, z, vz, 1, 1, -1);
			PutPlayerInVehicle(playerid, veh, 0);
			return 1;
		}
		if (strcmp(cmds[0], "/cc", true) == 0) {
			ChangeVehicleColor(veh, cmd2n, cmd3n);
			return 1;
		}
		if (strcmp(cmds[0], "/rv", true) == 0) {
			EQ_RespawnVehicles();
			return 1;
		}
		if (strcmp(cmds[0], "/r", true) == 0) {
			SpawnPlayer(cmd2n);
			return 1;
		}
		if (strcmp(cmds[0], "/g", true) == 0) {
			if (cmd3n == 0)
				cmd3n = 50;
			GivePlayerWeapon(playerid, cmd2n, cmd3n);
			return 1;
		}
		if (strcmp(cmds[0], "/sp", true) == 0) {
			TogglePlayerSpectating(playerid, 1);
			PlayerSpectatePlayer(playerid, cmd2n);
			return 1;
		}
		if (strcmp(cmds[0], "/sv", true) == 0) {
			TogglePlayerSpectating(playerid, 1);
			PlayerSpectateVehicle(playerid, cmd2n);
			return 1;
		}
		if (strcmp(cmds[0], "/so", true) == 0) {
			TogglePlayerSpectating(playerid, 0);
			return 1;
		}
		if (strcmp(cmds[0], "/s", true) == 0) {
			SetPlayerSkin(playerid, cmd2n);
			return 1;
		}
	}

	if (strcmp(cmds[0], "/help", true) == 0) {
		EQ_HelpBox(playerid);
		return 1;
	}
	if (strcmp(cmds[0], "/kill", true) == 0) {
		SetPlayerHealth(playerid, 0);
		return 1;
	}
	if (strcmp(cmds[0], "/ep", true) == 0) {
		GameTextForPlayer(playerid, "~g~Emergency parachute", 2000, 3);
		GivePlayerWeapon(playerid, WEAPON_PARACHUTE, 1);
		return 1;
	}

	EQ_ErrorMsg(playerid, "~r~Unknown command");
	return 1;
}