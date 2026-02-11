class CfgPatches {
  class Tracker {
    units[] = {"ModifiedFieldTransceiver"};
    weapons[] = {};
    requiredVersion = 0.1;
    requiredAddons[] = {"DZ_Data", "DZ_Gear_Radio", "CF", "VPPAdminTools"};
  };
};

class CfgMods {
  class Tracker {
    dir = "Tracker";
    name = "Tracker";
    credits = "codehead0";
    author = "codehead0";
    type = "mod";

    class defs {
      class worldScriptModule {
        files[] = {"Tracker/scripts/4_World"};
      };
      class missionScriptModule {
        files[] = {"Tracker/scripts/5_Mission"};
      };
    };
  };
};

class CfgVehicles {
  class BaseRadio;

  class ModifiedFieldTransceiver : BaseRadio {
    scope = 2;
    displayName = "Modified Field Transceiver";
    descriptionShort = "Field Transceiver with tracking device";
    itemSize[] = {3,3};
  };
};
