static const string USAGE_STRING = "Usage: /tracker <create|delete|list|set|reload>";
static const string SET_USAGE_1 = "Usage: /tracker set <settings_variable> <value>";
static const string SET_USAGE_2 = "Choose variable from: interval, mindistance, holder, gridinfo, playerinfo, landmarkinfo";
static const ref array<string> SET_ALLOWED_VARIABLES = {"interval", "updateinterval", "mindistance", "holder", "includeholder", "gridinfo", "playerinfo", "landmarkinfo"};

string BoolToString(bool state, string true_string="true", string false_string="false") {
  if (state) return true_string;
  return false_string;
}

string BoolToONOFF(bool state) { return BoolToString(state, "ON", "OFF"); }

void HandleTrackerCommand(PlayerBase caller, array<string> arguments) {
  if (!caller) return;

  if (arguments.Count() == 0) {
    caller.MessageImportant(USAGE_STRING);
    return;
  }

  switch (arguments.Get(0)) {
    case "create":
    case "new":
    case "add":
      if (arguments.Count() != 2) {
        caller.MessageImportant("Usage: /tracker create <name>");
        break;
      }
      CommandCreateTracker(caller, arguments.Get(1));
      break;

    case "delete":
    case "remove":
      if (arguments.Count() != 2) {
        caller.MessageImportant("Usage: /tracker delete <name>");
        break;
      }
      CommandDeleteTracker(caller, arguments.Get(1));
      break;

    case "list":
      CommandListTrackers(caller);
      break;

    case "set":
      if (arguments.Count() != 3 || SET_ALLOWED_VARIABLES.Find(arguments.Get(1)) == -1) {
        caller.MessageImportant(SET_USAGE_1);
        caller.MessageImportant(SET_USAGE_2);
        break;
      }
      CommandSetVariable(caller, arguments.Get(1), arguments.Get(2));
      break;

    case "reload":
      CommandReloadSettings(caller);
      break;

    default:
      caller.MessageImportant("Unknown tracker command. " + USAGE_STRING);
      break;
  }
}

void CommandCreateTracker(PlayerBase player, string name) {
  vector playerPosition = player.GetPosition();
  ModifiedFieldTransceiver tracker = ModifiedFieldTransceiver.Cast(GetGame().CreateObjectEx("ModifiedFieldTransceiver", playerPosition, ECE_PLACE_ON_SURFACE));

  if (!tracker) {
    player.MessageImportant("Error: tracker could not be created!");
    return;
  }

  tracker.SetTrackerName(name);
  player.MessageImportant("Tracker created: " + name);
}

void CommandDeleteTracker(PlayerBase player, string name) {
  bool success = TrackerManager.Get().DeleteByName(name);
  if (success) player.MessageImportant("Tracker " + name + " deleted");
  else player.MessageImportant("Error: deleting tracker " + name + " failed!");
}

void CommandListTrackers(PlayerBase player) {
  if (TrackerManager.Get().GetAll().Count() == 0) {
    player.MessageImportant("No registered trackers found");
  }

  TrackerManager.Get().BroadcastPositions(player, true);
}

void CommandSetVariable(PlayerBase player, string variable, string value) {
  variable.ToLower();
  value.ToLower();

  TrackerManager manager = TrackerManager.Get();

  if (variable == "interval" || variable == "updateinterval") {
    float interval = value.ToFloat();
    manager.SetInterval(interval);
    player.MessageImportant("Tracker update interval set to " + interval + " seconds");
    return;
  }

  if (variable == "mindistance") {
    float distance = value.ToFloat();
    manager.SetMinDistance(distance);
    player.MessageImportant("Tracker minimum distance for detailed information set to " + distance + " m");
    return;
  }

  bool state;

  if (variable == "holder" || variable == "includeholder") {
    state = (value == "on" || value == "1" || value == "true");
    manager.SetIncludeHolder(state);
    player.MessageImportant("The player holding a tracker " + BoolToString(state, "will now receive", "will no longer receive") + " tracker location updates.");
    return;
  }

  if (variable == "gridinfo") {
    state = (value == "on" || value == "1" || value == "true");
    manager.SetGridInfo(state);
    player.MessageImportant("Grid info: " + BoolToONOFF(state));
    return;
  }

  if (variable == "playerinfo") {
    state = (value == "on" || value == "1" || value == "true");
    manager.SetPlayerInfo(state);
    player.MessageImportant("Player distance/direction info: " + BoolToONOFF(state));
    return;
  }

  if (variable == "landmarkinfo") {
    state = (value == "on" || value == "1" || value == "true");
    manager.SetLandmarkInfo(state);
    player.MessageImportant("Landmark distance/direction info: " + BoolToONOFF(state));
    return;
  }
}

void CommandReloadSettings(PlayerBase player) {
  TrackerManager.Get().LoadSettings();
  player.MessageImportant("Reloaded settings!");
}

class TrackerCommandHandlerChatModule : ChatCommand {
  override void ExecuteCommand(PlayerBase caller, array<Man> targets, array<string> args) {
    if(caller == null) return;

    string callerID   = caller.VPlayerGetSteamId();
    string callerName = caller.VPlayerGetName();

    array<string> arguments = new array<string>;
    string argumentString = args.Get(0);
    argumentString.Split(" ", arguments);

    GetSimpleLogger().Log(string.Format("\"%1\" (steamid=%2) used command /tracker %3", callerName, callerID, argumentString));
    GetWebHooksManager().PostData(AdminActivityMessage, new AdminActivityMessage(callerID, callerName, "Chat Command Manager: /tracker " + argumentString + " command used"));
    
    HandleTrackerCommand(caller, arguments);
  }
}

modded class ChatCommandManager {
  override void OnInit() {
    super.OnInit();
    AddChatCommand(new TrackerCommandHandlerChatModule("/tracker", 0, "Chat:Tracker"));
  }
}
