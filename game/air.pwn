#include <a_npc>

new count = 1, bool:running;
new name[8];

main(){}

forward NextAction();
public NextAction()
{
	if (count > 2) count = 0;
	format(name, sizeof(name), "air%d", count);
	++count;
	StartRecordingPlayback(PLAYER_RECORDING_TYPE_DRIVER, name);
}

public OnRecordingPlaybackEnd()
{
	SetTimer("NextAction", 10000, false);
}

public OnNPCEnterVehicle(vehicleid, seatid)
{
	if (!running) {
		StartRecordingPlayback(PLAYER_RECORDING_TYPE_DRIVER, "air0");
		running = true;
	}
}