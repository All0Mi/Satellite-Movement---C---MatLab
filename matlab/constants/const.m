classdef const
    properties
        earthRadius         = 6371;                 % km
        gravitationalConst  = 6.6743e-11;           % m3 kg-1 s-2
        earthMass           = 5.97219e24;           % kg
        EarthAngSpeed = 360/(24*60*60) * pi / 180;  % rad/s
    end
end