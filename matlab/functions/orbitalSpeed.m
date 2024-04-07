function speed = orbitalSpeed(height)
% ORBITALSPEED Orbital speed (rad/s) of satelite on given height (km)

    addpath("constants/");
    c = const;
    speed = sqrt((c.gravitationalConst*c.earthMass)/((c.earthRadius+height)*1000))/1000;
    speed = speed/(((c.earthRadius+height)));
end

