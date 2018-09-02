#define VEH_DELAY 90
#define VEH_DELAY_STATIC 1

EQ_AddVehicles()
{
	// Police bikes
	AddStaticVehicleEx(586,-1720.473,999.756,17.300,90.000,0,0,VEH_DELAY); // Garage bike 1
	AddStaticVehicleEx(586,-1720.470,1007.363,17.300,90.000,0,0,VEH_DELAY); // 2
	AddStaticVehicleEx(586,-1763.614,955.450,24.500,90.000,0,0,VEH_DELAY); // Outdoor
	// Cars
	AddStaticVehicleEx(516,-1687.184,1053.076,17.600,90.000,1,1,VEH_DELAY); // cleric
	AddStaticVehicleEx(609,-1687.650,999.736,17.800,90.000,101,0,VEH_DELAY, 1); // Boxville 1
	AddStaticVehicleEx(609,-1687.650,1032.212,17.800,90.000,101,0,VEH_DELAY, 1); // 2
	AddStaticVehicleEx(598,-1736.092,1016.036,17.500,270.000,101,0,VEH_DELAY); // LVPD 1
	AddStaticVehicleEx(598,-1736.092,1032.367,17.500,270.000,101,0,VEH_DELAY); // 2
	AddStaticVehicleEx(482,-1776.415,912.173,25.000,270.000,0,0,VEH_DELAY); // Burrito
	AddStaticVehicleEx(413,-1743.943,912.173,25.000,270.000,0,0,VEH_DELAY); // Pony
	// Dune
	AddStaticVehicleEx(573,-1800.2009,1013.9730,25.3847,179.8258,0,101,VEH_DELAY, 1);
	AddStaticVehicleEx(573,-1860.5629,912.3922,35.6596,270.2686,0,101,VEH_DELAY, 1);
	AddStaticVehicleEx(573,-1516.4146,1018.4106,7.8379,179.5668,0,101,VEH_DELAY, 1);
	// Quad
	AddStaticVehicleEx(471,-1600.148,897.752,8.710,0.000,101,0,VEH_DELAY);
	AddStaticVehicleEx(471,-1495.571,944.536,6.670,90.000,101,0,VEH_DELAY);
	// Blista
	AddStaticVehicleEx(496,-1747.252,948.715,24.460,90.000,101,0,VEH_DELAY, 1);

	// Tugs
	AddStaticVehicleEx(583,-1783.255,750.952,24.600,270.000,1,1,VEH_DELAY);
	AddStaticVehicleEx(583,-1787.177,785.791,24.600,0.000,1,1,VEH_DELAY);
	AddStaticVehicleEx(583,-1624.477,858.517,7.200,270.000,1,1,VEH_DELAY);
	AddStaticVehicleEx(583,-1581.888,651.858,6.900,0.000,1,1,VEH_DELAY);
	AddStaticVehicleEx(589,-1597.440,857.910,7.300,269.022,1,0,VEH_DELAY);
	// Baggage
	AddStaticVehicleEx(485,-1742.468,813.793,24.700,270.000,1,1,VEH_DELAY);
	AddStaticVehicleEx(485,-1496.457,844.452,7.000,90.000,1,1,VEH_DELAY);

	// Rebel cars
	AddStaticVehicleEx(543,-2061.757,303.676,35.600,180.000,6,0,VEH_DELAY);
	AddStaticVehicleEx(605,-2129.682,177.873,35.200,270.000,17,0,VEH_DELAY);
	AddStaticVehicleEx(483,-2063.279,228.757,35.900,0.000,4,28,VEH_DELAY);
	AddStaticVehicleEx(483,-2104.240,149.945,35.300,270.000,7,30,VEH_DELAY);
	AddStaticVehicleEx(591,-2086.971,163.189,35.800,320.000,10,0,VEH_DELAY_STATIC);
	AddStaticVehicleEx(450,-2034.459,253.788,35.500,0.000,16,0,VEH_DELAY_STATIC);
	AddStaticVehicleEx(566,-2061.369,271.336,35.500,270.000,229,0,VEH_DELAY);
	AddStaticVehicleEx(440,-2045.355,230.188,35.500,225.000,183,0,VEH_DELAY);
	AddStaticVehicleEx(531,-1995.337,215.690,27.800,270.000,161,0,VEH_DELAY);
	AddStaticVehicleEx(578,-2028.987,160.084,29.600,0.000,211,0,VEH_DELAY);

	// Civil
	AddStaticVehicleEx(400,-1674.543,1205.914,13.900,270.000,198,0,VEH_DELAY);
	AddStaticVehicleEx(403,-1710.378,391.527,7.900,225.000,209,0,VEH_DELAY);
	AddStaticVehicleEx(404,-1684.835,416.783,7.000,315.000,142,158,VEH_DELAY);
	AddStaticVehicleEx(414,-1806.711,398.197,17.000,315.000,242,0,VEH_DELAY);
	AddStaticVehicleEx(414,-1851.745,119.007,15.400,270.000,202,0,VEH_DELAY);
	AddStaticVehicleEx(515,-1824.362,64.694,16.300,180.000,3,15,VEH_DELAY);
	AddStaticVehicleEx(486,-1719.187,593.176,25.300,315.000,0,0,VEH_DELAY);
	AddStaticVehicleEx(404,-1805.895,577.080,35.100,270.000,234,0,VEH_DELAY);
	AddStaticVehicleEx(483,-1941.368,585.242,35.300,0.000,5,1,VEH_DELAY);
	AddStaticVehicleEx(483,-2096.102,642.844,52.500,180.000,217,215,VEH_DELAY);
	AddStaticVehicleEx(568,-2150.012,-146.482,36.500,270.000,1,1,VEH_DELAY);
	AddStaticVehicleEx(568,-2183.437,-218.980,36.500,0.000,1,1,VEH_DELAY);
	AddStaticVehicleEx(455,-2123.400,-123.157,35.900,180.000,244,0,VEH_DELAY);
	AddStaticVehicleEx(455,-2105.838,-238.054,35.900,45.000,201,0,VEH_DELAY);
	AddStaticVehicleEx(437,-2073.156,-95.731,35.400,270.000,162,169,VEH_DELAY);
	AddStaticVehicleEx(544,-2060.502,56.138,28.800,270.000,175,0,VEH_DELAY);
	AddStaticVehicleEx(544,-2054.689,88.690,28.800,180.000,175,0,VEH_DELAY);
	AddStaticVehicleEx(408,-1500.024,729.192,7.900,90.000,138,0,VEH_DELAY);
	AddStaticVehicleEx(408,-1924.210,888.045,36.000,270.000,138,0,VEH_DELAY);
	AddStaticVehicleEx(408,-2120.614,437.785,35.900,180.000,138,0,VEH_DELAY);
	AddStaticVehicleEx(408,-2218.729,424.040,35.900,180.000,138,0,VEH_DELAY);
	AddStaticVehicleEx(408,-2201.386,104.570,36.000,270.000,138,0,VEH_DELAY);
	AddStaticVehicleEx(406,-2271.131,531.666,36.700,0.000,0,0,VEH_DELAY);
	AddStaticVehicleEx(406,-1662.132,1099.211,25.300,270.000,0,0,VEH_DELAY);
	AddStaticVehicleEx(409,-2186.585,516.811,34.972,90.000,1,0,VEH_DELAY);
	AddStaticVehicleEx(439,-2046.396,559.575,34.912,90.000,6,0,VEH_DELAY);
	AddStaticVehicleEx(541,-1978.810,430.783,24.914,180.000,3,1,VEH_DELAY);
	AddStaticVehicleEx(474,-2014.939,755.322,45.209,0.000,44,0,VEH_DELAY);

	// Wang cars
	AddStaticVehicleEx(401,-1986.486,264.639,34.960,180.000,44,0,VEH_DELAY);
	AddStaticVehicleEx(401,-1950.003,257.800,35.250,0.000,43,0,VEH_DELAY);
	AddStaticVehicleEx(402,-1955.409,303.485,40.880,180.000,79,0,VEH_DELAY);
}

EQ_AddObjects()
{
	// SFPD Closed
	CreateObject(10828, -1631.00000, 690.00000, 9.00000, 0.00000, 0.00000, 0.00000);

	// Police lamps
	CreateObject(1278, -1766.75000, 945.00000, 20.00000, 0.00000, 0.00000, 0.00000);
	CreateObject(1278, -1744.20000, 945.00000, 20.00000, 0.00000, 0.00000, 0.00000);
	// Police fence
	CreateObject(978, -1755.00000, 944.00000, 24.70000, 0.00000, 0.00000, 180.00000);
	// Gates
	CreateObject(10828, -1873.87000, 923.00000, 45.00000, 0.00000, 0.00000, 90.00000);
	CreateObject(10841, -1874.60000, 942.50000, 38.00000, 0.00000, -90.00000, 90.00000);
	CreateObject(10841, -1872.70000, 942.50000, 38.00000, 0.00000, -90.00000, 90.00000);
	CreateObject(10828, -1869.00000, 847.00000, 45.00000, 0.00000, 0.00000, 90.00000);
	CreateObject(10841, -1870.50000, 827.75000, 38.00000, 0.00000, 90.00000, 90.00000);
	CreateObject(10841, -1868.00000, 827.75000, 38.00000, 0.00000, 90.00000, 90.00000);
	CreateObject(10828, -1794.10000, 1068.00000, 52.00000, 0.00000, 0.00000, 0.00000);
	CreateObject(10828, -2004.00000, 969.70000, 56.55000, 0.00000, 0.00000, 0.00000);
	CreateObject(10828, -2019.70000, 943.00000, 56.55000, 0.00000, 0.00000, 90.00000);
	CreateObject(10828, -2019.70000, 907.60000, 56.55000, 0.00000, 0.00000, 90.00000);
	// Gates LOD
	CreateObject(10893, -1873.87000, 923.00000, 45.00000, 0.00000, 0.00000, 90.00000);
	CreateObject(10893, -1869.00000, 847.00000, 45.00000, 0.00000, 0.00000, 90.00000);
	CreateObject(10893, -1794.10000, 1068.00000, 52.00000, 0.00000, 0.00000, 0.00000);
	CreateObject(10893, -2004.00000, 969.70000, 56.55000, 0.00000, 0.00000, 0.00000);
	CreateObject(10893, -2019.70000, 943.00000, 56.55000, 0.00000, 0.00000, 90.00000);
	CreateObject(10893, -2019.70000, 907.60000, 56.55000, 0.00000, 0.00000, 90.00000);
	// Room
	CreateObject(16093, -1812.00000, 925.00000, 23.65000, 0.00000, 0.00000, 90.00000);
/*
	// Airport fence
	CreateObject(10885, -1230.80000, -460.70000, 16.18000, 0.00000, 0.00000, 45.00000);
	CreateObject(10885, -1234.40000, -291.60000, 16.18000, 0.00000, 0.00000, 45.00000);
	CreateObject(10885, -1237.90000, -123.60000, 16.18000, 0.00000, 0.00000, 45.00000);
	CreateObject(10885, -1273.50000, 12.00000, 16.18000, 0.00000, 0.00000, 60.00000);
	CreateObject(10885, -1312.20000, 101.30000, 16.18000, 0.00000, 0.00000, 90.00000);
*/
	// Emergency stairs
	CreateObject(3753, -1406.00000, 138.00000, 2.50000, 0.00000, 0.00000, 45.00000);
	CreateObject(3753, -1743.40000, -445.00000, 2.50000, 0.00000, 0.00000, 90.00000);
	CreateObject(3753, -1621.80000, -76.90000, 2.50000, 0.00000, 0.00000, 45.00000);
	CreateObject(3753, -1510.50000, 527.30000, -4.00000, 0.00000, 0.00000, -90.00000);
	CreateObject(3753, -1696.10000, -650.80000, 2.50000, 0.00000, 0.00000, 145.00000);
/*
	// City exit stop
	CreateObject(3578, -1760.80005, -685.20001, 24.00000, 0.00000, 0.00000, 10.00000);
	CreateObject(3578, -1813.60000, -686.50000, 22.50000, 0.00000, 0.00000, 0.00000);
	CreateObject(981, -1904.22156, -687.35132, 41.82000, 3.00000, 0.00000, 180.00000);
	CreateObject(3578, -1986.78870, -689.74323, 32.02000, 0.00000, -1.00000, 0.00000);
	CreateObject(3578, -2259.20000, -686.50000, 66.92000, 0.00000, -5.00000, 25.00000);
*/
	// Big ear
	CreateObject(16613, -1478.00000, 920.00000, 31.00000, 0.00000, 0.00000, 180.00000);
	CreateObject(16614, -1478.00000, 920.00000, 31.00000, 0.00000, 0.00000, 180.00000);
	CreateObject(3255, -1504.00000, 738.00000, 6.50000, 0.00000, 0.00000, 90.00000);
	CreateObject(3629, -1475.00000, 920.10000, 12.75000, 0.00000, 0.00000, 90.00000);
/*
	// SF Stop
	CreateObject(3578, -2281.00000, 1098.70000, 79.90000, 0.00000, 2.00000, 80.00000);
	CreateObject(3578, -2285.50000, 964.30000, 65.70000, 0.00000, 0.00000, 90.00000);
	CreateObject(3578, -2285.50000, 953.62689, 65.70000, 0.00000, 0.00000, 90.00000);
	CreateObject(3578, -2284.60000, 813.90000, 49.00000, 0.00000, 0.00000, 90.00000);
	CreateObject(3578, -2284.60000, 802.90000, 49.00000, 0.00000, 0.00000, 90.00000);
	CreateObject(3578, -2282.10000, 727.50000, 49.10000, 0.00000, 0.00000, 90.00000);
	CreateObject(3578, -2284.60000, 673.90000, 48.50000, 0.00000, 0.00000, 90.00000);
	CreateObject(3578, -2284.60000, 662.90000, 48.50000, 0.00000, 0.00000, 90.00000);
	CreateObject(3578, -2284.90000, 577.70000, 34.90000, 0.00000, 0.00000, 90.00000);
	CreateObject(3578, -2284.90000, 566.70000, 34.90000, 0.00000, 0.00000, 90.00000);
	CreateObject(3578, -2284.90000, 555.70000, 34.90000, 0.00000, 0.00000, 90.00000);
	CreateObject(3578, -2272.90000, 515.60000, 34.80000, 0.00000, 0.00000, -45.00000);
	CreateObject(3578, -2269.30000, 505.30000, 34.80000, 0.00000, 0.00000, 90.00000);
	CreateObject(8148, -2290.00000, 121.15000, 37.00000, 0.00000, 0.00000, 0.00000);
	CreateObject(8148, -2290.00000, 283.15000, 37.00000, 0.00000, 0.00000, 0.00000);
	CreateObject(8210, -2290.00000, 391.62000, 37.00000, 0.00000, 0.00000, 90.00000);
*/
}

EQ_RemoveBuildings(playerid)
{
	// Lights
	RemoveBuildingForPlayer(playerid, 1375, -2054.000, 477.575, 35.170, 2000.0);
	RemoveBuildingForPlayer(playerid, 1283, -2054.000, 477.575, 35.170, 2000.0);
	RemoveBuildingForPlayer(playerid, 1284, -2054.000, 477.575, 35.170, 2000.0);
	RemoveBuildingForPlayer(playerid, 1350, -2054.000, 477.575, 35.170, 2000.0);
	RemoveBuildingForPlayer(playerid, 1290, -2054.000, 477.575, 35.170, 2000.0);
	RemoveBuildingForPlayer(playerid, 1232, -2054.000, 477.575, 35.170, 2000.0);

	// Trees
	RemoveBuildingForPlayer(playerid, 717, -2054.000, 477.575, 35.170, 2000.0);
	RemoveBuildingForPlayer(playerid, 737, -2054.000, 477.575, 35.170, 2000.0);
	RemoveBuildingForPlayer(playerid, 715, -2054.000, 477.575, 35.170, 2000.0);
	RemoveBuildingForPlayer(playerid, 673, -2054.000, 477.575, 35.170, 2000.0);
	RemoveBuildingForPlayer(playerid, 731, -2054.000, 477.575, 35.170, 2000.0);
	RemoveBuildingForPlayer(playerid, 733, -2054.000, 477.575, 35.170, 2000.0);

	// Red bridge
	RemoveBuildingForPlayer(playerid, 9687, -2681.4922, 1684.4609, 120.4531, 0.25);
	RemoveBuildingForPlayer(playerid, 9689, -2681.4922, 1684.4609, 120.4531, 0.25);
	RemoveBuildingForPlayer(playerid, 9691, -2681.4922, 1847.9375, 120.0859, 0.25);
	RemoveBuildingForPlayer(playerid, 9693, -2681.4922, 1847.9375, 120.0859, 0.25);

	// White bridge
	RemoveBuildingForPlayer(playerid, 10822, -1336.8125, 892.7578, 57.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 11251, -1336.8125, 892.7578, 57.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 11381, -1349.3281, 879.4219, 43.0313, 0.25);

	// Railroad bridge
	RemoveBuildingForPlayer(playerid, 11253, -1385.7188, 670.8047, 42.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 11254, -1132.0703, 855.0859, 42.3281, 0.25);
	RemoveBuildingForPlayer(playerid, 11256, -1432.6094, 639.4844, 35.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 11257, -1368.9844, 682.9609, 31.6953, 0.25);
	RemoveBuildingForPlayer(playerid, 11258, -1319.5938, 716.7813, 42.5313, 0.25);
	RemoveBuildingForPlayer(playerid, 11259, -1142.0859, 847.7188, 34.5859, 0.25);
	RemoveBuildingForPlayer(playerid, 11260, -1198.3984, 808.6328, 42.5313, 0.25);
	RemoveBuildingForPlayer(playerid, 11263, -1385.7188, 670.8047, 42.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 11264, -1432.6094, 639.4844, 35.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 11265, -1319.5938, 716.7813, 42.5313, 0.25);
	RemoveBuildingForPlayer(playerid, 11266, -1198.3984, 808.6328, 42.5313, 0.25);
	RemoveBuildingForPlayer(playerid, 11268, -1132.0703, 855.0859, 42.3281, 0.25);

	// Airport fences
	RemoveBuildingForPlayer(playerid, 10807, -1617.4219, -561.0234, 16.2500, 0.25);
	RemoveBuildingForPlayer(playerid, 10808, -1680.6172, -478.0938, 16.2500, 0.25);
}