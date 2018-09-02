#define SECURE_IP_LIMIT 2 // = Max connections from one single IP
#define SECURE_SAME_IP_CONNECT 4 // = The number of connects from the same IP before banning the flooder
#define SECURE_TIMELIMIT 3500 // = The time span between connects, adjust it to your own specifications
new sameIP = 0, joinStamp, ban_s[25], exceed = 0;

EQ_BanPlayer(playerid, reason[])
{
	BanEx(playerid, reason);
}

GetStampIP(playerid)
{
	new S_IP[16];
	joinStamp = GetTickCount();
	GetPlayerIp(playerid, S_IP, 16);
	format(ban_s, 16, "%s", S_IP);
}

EQ_SecureCheck(playerid, connIP[])
{
	new compareIP[16];
	new numberIP = 0;

	if (IsPlayerNPC(playerid)) {
		EQ_BanPlayer(playerid, "AUTO: NPC"); // Ban is the safest thing here, as if you kick, they can still flood you with endless connections
		return 0;
	}

	for (new i = 0; i < MAX_PLAYERS; i++) {
		if (IsPlayerConnected(i)) {
			GetPlayerIp(i, compareIP, 16);
			if (!strcmp(compareIP, connIP))
				numberIP++;
		}
	}
	if ((GetTickCount() - joinStamp) < SECURE_TIMELIMIT)
		exceed = 1;
	else
		exceed = 0;
	if (strcmp(ban_s, connIP, false) == 0 && exceed == 1) {
		sameIP++;
		if (sameIP > SECURE_SAME_IP_CONNECT) {
			EQ_BanPlayer(playerid, "AUTO: sameIP > SECURE_SAME_IP_CONNECT");
			sameIP = 0;
			return 0;
		}
	} else {
		sameIP = 0;
	}
	if (numberIP > SECURE_IP_LIMIT) {
		Kick(playerid);
		return 0;
	}
	GetStampIP(playerid);

	return 1;
}