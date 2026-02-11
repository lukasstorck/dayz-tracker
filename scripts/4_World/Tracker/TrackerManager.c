static const string TRACKERSETTINGSFILE = "$profile:tracker_settings.json";

static const ref array<string> COMPASS = {
  "north",
  "north-north-east",
  "north-east",
  "east-north-east",
  "east",
  "east-south-east",
  "south-east",
  "south-south-east",
  "south",
  "south-south-west",
  "south-west",
  "west-south-west",
  "west",
  "west-north-west",
  "north-west",
  "north-north-west"
};


void GetDirectionAndDistance(vector from, vector to, out string direction, out float distance) {
  vector diff = to - from;
  diff[1] = 0;

  distance = diff.Length();

  float angle = Math.Atan2(diff[0], diff[2]) * Math.RAD2DEG;
  angle = Math.ModFloat(angle + 360 + 11.25, 360);

  int index = Math.Floor(angle / 22.5);
  direction = COMPASS[index];
}


class TrackerSettings {
  float updateInterval = 60;
  float minDistance = 50;
  bool includeHolder = false;
  bool gridInfo = true;
  bool playerInfo = true;
  bool landmarkInfo = true;

  ref map<string, vector> landmarks;

  void TrackerSettings() {
    landmarks = new map<string, vector>();

    // Unmarked
    landmarks.Insert("Tri Kresta", "331 0 9379");
    landmarks.Insert("Radio Zenit", "8079 0 9350");

    // Camps
    landmarks.Insert("Arsenyevo (Camp)", "8505 0 13951");
    landmarks.Insert("Camp Builder", "7034 0 4329");
    landmarks.Insert("Camp Friendship", "11489 0 10644");
    landmarks.Insert("Kometa (Camp)", "10319 0 3487");
    landmarks.Insert("Camp Metallurgist", "1076 0 6629");
    landmarks.Insert("Nadezhda (Camp)", "7226 0 6983");
    landmarks.Insert("Pobeda (Camp)", "3666 0 14869");
    landmarks.Insert("Proud Chernarus (Camp)", "3196 0 6102");
    landmarks.Insert("Romashka (Camp)", "8136 0 10963");
    landmarks.Insert("Camp Scholar", "14834 0 14568");
    landmarks.Insert("Youth Pioneer (Camp)", "11154 0 7038");

    // Castles
    landmarks.Insert("Devil's Castle", "6893 0 11432");
    landmarks.Insert("Dwarf's Castle", "7427 0 9104");
    landmarks.Insert("Klyuch Castle", "9280 0 13475");
    landmarks.Insert("Krona Castle", "1410 0 9247");
    landmarks.Insert("Rog Castle", "11247 0 4293");
    landmarks.Insert("Storozh Castle", "2716 0 1292");
    landmarks.Insert("Voron Castle", "13438 0 3299");
    landmarks.Insert("Zolotar Castle", "10195 0 12026");
    landmarks.Insert("Zub Castle", "6530 0 5589");

    // Hills and Mountains
    // landmarks.Insert("Altar (Hill)", "8160 0 9120");
    // landmarks.Insert("Bald Mountain", "");
    // landmarks.Insert("Baranchik (Hill)", "10144 0 6210");
    // landmarks.Insert("Bashnya (Hill)", "");
    // landmarks.Insert("Black Mountain", "");
    // landmarks.Insert("Bolshoy Kotel (Hill)", "");
    // landmarks.Insert("Dazhbog (Hill)", "");
    // landmarks.Insert("Dobry (Hill)", "");
    // landmarks.Insert("Dubina (Hill)", "");
    // landmarks.Insert("Erbenka (Hill)", "");
    // landmarks.Insert("Green Mountain", "3721 0 5990");
    // landmarks.Insert("Kalmyk (Hill)", "");
    // landmarks.Insert("Kikimora (Hill)", "");
    // landmarks.Insert("Klen (Hill)", "");
    // landmarks.Insert("Koman (Hill)", "1661 0 7409");
    // landmarks.Insert("Kopyto (Hill)", "");
    // landmarks.Insert("Kozlov's Peak (Hill)", "");
    // landmarks.Insert("Kurgan (Hill)", "");
    // landmarks.Insert("Kustryk (Hill)", "");
    // landmarks.Insert("Malinovka (Hill)", "");
    // landmarks.Insert("Mayak (Hill)", "12320 0 4559");
    // landmarks.Insert("Misty Hill", "");
    // landmarks.Insert("Olsha (Hill)", "12945 0 12764");
    // landmarks.Insert("Ostrog (Hill)", "");
    // landmarks.Insert("Ostry (Hill)", "");
    // landmarks.Insert("Pop Ivan (Hill)", "");
    // landmarks.Insert("Saint Roman (Hill)", "");
    // landmarks.Insert("Shishok (Hill)", "");
    // landmarks.Insert("Simurg (Hill)", "");
    // landmarks.Insert("Sokol (Hill)", "");
    // landmarks.Insert("Tokarnya (Hill)", "8879 0 5677");
    // landmarks.Insert("Veresnik (Hill)", "");
    // landmarks.Insert("Viselitsa (Hill)", "");
    // landmarks.Insert("Vysokiy Kamen (Hill)", "");
    // landmarks.Insert("Vysota (Hill)", "6585 0 3404");
    // landmarks.Insert("Windy Mountain", "");
    // landmarks.Insert("Wolf Peak (Hill)", "");

    // Lakes, Ponds and Dams
    // landmarks.Insert("Black Lake", "13369 0 12041");
    // landmarks.Insert("Deep Lake", "");
    // landmarks.Insert("Eagle Lake", "");
    // landmarks.Insert("Glaza (Pond)", "7351 0 9274");
    // landmarks.Insert("Ozerko (Pond)", "6820 0 4492");
    // landmarks.Insert("Pobeda Dam", "");
    // landmarks.Insert("Prud (Pond)", "6577 0 9279");
    // landmarks.Insert("Tishina Dam", "1196 0 6364");
    // landmarks.Insert("Topolka Dam", "10294 0 3692");
    // landmarks.Insert("Verbnik (Pond)", "4425 0 9103");
    // landmarks.Insert("Willow Lake", "13251 0 11570");

    // Military Bases and Airfields
    landmarks.Insert("Balota Airfield", "5056 0 2375");
    landmarks.Insert("Green Mountain Military Base", "3721 0 5990");
    landmarks.Insert("Kamensk Military Base", "7872 0 14698");
    landmarks.Insert("Krasnostav Airfield", "11207 0 12397");
    landmarks.Insert("Pavlovo Military Base", "2144 0 3341");
    landmarks.Insert("Tisy Military Base Tents", "1507 0 13604");
    landmarks.Insert("Tisy Military Base Prison", "1685 0 14207");
    landmarks.Insert("Veresnik Military Base (VMC)", "4509 0 8278");
    landmarks.Insert("Vybor Air Base North Tents", "4194 0 11041");
    landmarks.Insert("Vybor Air Base ATC", "4635 0 10441");
    landmarks.Insert("Zelenogorsk Military Base", "2490 0 5094");

    // Sea and Coast
    // landmarks.Insert("Black Bay", "");
    // landmarks.Insert("Calm Bay", "");
    // landmarks.Insert("Green Bay", "");
    // landmarks.Insert("Green Sea", "");
    // landmarks.Insert("Guba Bay", "14333 0 13143");
    // landmarks.Insert("Murky Bay", "");
    // landmarks.Insert("Nizhniy Bay", "13036 0 8510");
    // landmarks.Insert("Skalisty Strait", "13308 0 3644");

    // Major Towns
    landmarks.Insert("Chernogorsk Town Center", "6516 0 2507");
    landmarks.Insert("Novodmitrovsk Town Center", "11488 0 14299");

    // Towns
    landmarks.Insert("Berezino Harbor", "13165 0 10057");
    landmarks.Insert("Berezino Hospital", "11925 0 9073");
    landmarks.Insert("Berezino Town Center", "12329 0 9619");
    landmarks.Insert("Chernaya Polyana Town Center", "12127 0 13758");
    landmarks.Insert("Dubovo Town Center", "6706 0 3586");
    landmarks.Insert("Elektrozavodsk Harbor", "10160 0 1753");
    landmarks.Insert("Elektrozavodsk Town Center", "10329 0 2161");
    landmarks.Insert("Gorka Town Center", "9458 0 8817");
    landmarks.Insert("Krasnostav Town Center", "11129 0 12283");
    landmarks.Insert("Novaya Petrovka Town Center", "3484 0 13003");
    landmarks.Insert("Novoselki Town Center", "6130 0 3246");
    landmarks.Insert("Polyana Town Center", "10690 0 8049");
    landmarks.Insert("Severograd Town Center", "7969 0 12693");
    landmarks.Insert("Solnechny Town Center", "13415 0 6248");
    landmarks.Insert("Stary Sobor Town Center", "6061 0 7772");
    landmarks.Insert("Svetloyarsk Town Center", "13907 0 13232");
    landmarks.Insert("Vybor Town Center", "3804 0 8870");
    landmarks.Insert("Vysotovo Town Center", "5734 0 2542");
    landmarks.Insert("Zelenogorsk Town Center", "2727 0 5315");

    // Villages
    landmarks.Insert("Balota Village Center", "4493 0 2456");
    landmarks.Insert("Belaya Polyana Village Center", "14124 0 14969");
    landmarks.Insert("Berezhki Village Center", "15114 0 13838");
    landmarks.Insert("Bogatyrka Village Center", "1556 0 8953");
    landmarks.Insert("Bor Village Center", "3327 0 3940");
    landmarks.Insert("Dobroye Village Center", "12936 0 15059");
    landmarks.Insert("Dolina Village Center", "11286 0 6556");
    landmarks.Insert("Drozhino Village Center", "3378 0 4920");
    landmarks.Insert("Dubrovka Village Center", "10430 0 9838");
    landmarks.Insert("Grishino Village Center", "5973 0 10332");
    landmarks.Insert("Guglovo Village Center", "8432 0 6657");
    landmarks.Insert("Gvozdno Village Center", "8586 0 11908");
    landmarks.Insert("Kabanino Village Center", "5331 0 8586");
    landmarks.Insert("Kalinovka Village Center", "7593 0 13426");
    landmarks.Insert("Kamenka Village Center", "1874 0 2233");
    landmarks.Insert("Kamensk Village Center", "6665 0 14474");
    landmarks.Insert("Kamyshovo Village Center", "12074 0 3555");
    landmarks.Insert("Karmanovka Village Center", "12692 0 14618");
    landmarks.Insert("Khelm Village Center", "12292 0 10890");
    landmarks.Insert("Komarovo Village Center", "3642 0 2469");
    landmarks.Insert("Kozlovka Village Center", "4402 0 4622");
    landmarks.Insert("Krasnoye Village Center", "6455 0 14977");
    landmarks.Insert("Kumyrna Village Center", "8365 0 5983");
    landmarks.Insert("Lopatino Village Center", "2736 0 9958");
    landmarks.Insert("Mogilevka Village Center", "7548 0 5166");
    landmarks.Insert("Msta Village Center", "11316 0 5483");
    landmarks.Insert("Myshkino Village Center", "2010 0 7286");
    landmarks.Insert("Nadezhdino Village Center", "5840 0 4773");
    landmarks.Insert("Nagornoye Village Center", "9320 0 14610");
    landmarks.Insert("Nizhnee Village Center", "12933 0 8045");
    landmarks.Insert("Novy Sobor Village Center", "7094 0 7690");
    landmarks.Insert("Olsha Village Center", "13354 0 12894");
    landmarks.Insert("Orlovets Village Center", "12155 0 7263");
    landmarks.Insert("Pavlovo Village Center", "1698 0 3818");
    landmarks.Insert("Pogorevka Village Center", "4460 0 6410");
    landmarks.Insert("Polesovo Village Center", "5885 0 13542");
    landmarks.Insert("Prigorodki Village Center", "7689 0 3217");
    landmarks.Insert("Pulkovo Village Center", "4918 0 5633");
    landmarks.Insert("Pusta Village Center", "8437 0 3710");
    landmarks.Insert("Pustoshka Village Center", "3062 0 7914");
    landmarks.Insert("Ratnoye Village Center", "6270 0 12700");
    landmarks.Insert("Rogovo Village Center", "4756 0 6773");
    landmarks.Insert("Shakovka Village Center", "9672 0 6553");
    landmarks.Insert("Sinystok Village Center", "1457 0 11960");
    landmarks.Insert("Skalisty Village Center", "13625 0 2963");
    landmarks.Insert("Sosnovka Village Center", "2524 0 6374");
    landmarks.Insert("Staroye Village Center", "10140 0 5445");
    landmarks.Insert("Stary Yar Village Center", "4980 0 15075");
    landmarks.Insert("Svergino Village Center", "9529 0 13762");
    landmarks.Insert("Tisy Village Center", "3416 0 14792");
    landmarks.Insert("Topolniki Village Center", "2886 0 12414");
    landmarks.Insert("Tulga Village Center", "12687 0 4392");
    landmarks.Insert("Turovo Village Center", "13575 0 14083");
    landmarks.Insert("Vavilovo Village Center", "2203 0 11101");
    landmarks.Insert("Verkhnaya Dubrovka Village Center", "9930 0 10391");
    landmarks.Insert("Vyshnoye Village Center", "5644 0 5925");
    landmarks.Insert("Zabolotye Village Center", "1159 0 9989");
    landmarks.Insert("Zaprudnoye Village Center", "5116 0 12750");
    landmarks.Insert("Zvir Village Center", "582 0 5286");
  }
}

class TrackerManager {
  static ref TrackerManager s_Instance;
  protected ref array<ModifiedFieldTransceiver> m_Trackers;
  protected float m_TimeAccu;
  protected ref TrackerSettings m_Settings;

  void TrackerManager() {
    m_Trackers = new array<ModifiedFieldTransceiver>();
    LoadSettings();
  }

  void LoadSettings() {
    if (!FileExist(TRACKERSETTINGSFILE)) {
      TrackerSettings defaultSettings = new TrackerSettings();
      JsonFileLoader<TrackerSettings>.JsonSaveFile(TRACKERSETTINGSFILE, defaultSettings);
    }

    m_Settings = new TrackerSettings();
    JsonFileLoader<TrackerSettings>.JsonLoadFile(TRACKERSETTINGSFILE, m_Settings);
  }

  static TrackerManager Get() {
    if (!s_Instance) s_Instance = new TrackerManager();
    return s_Instance;
  }

  void SetInterval(float seconds) { m_Settings.updateInterval = seconds; }
  void SetMinDistance(float distance) { m_Settings.minDistance = distance; }
  void SetIncludeHolder(bool state) { m_Settings.includeHolder = state; }
  void SetGridInfo(bool state) { m_Settings.gridInfo = state; }
  void SetPlayerInfo(bool state) { m_Settings.playerInfo = state; }
  void SetLandmarkInfo(bool state) { m_Settings.landmarkInfo = state; }

  array<ModifiedFieldTransceiver> GetAll() { return m_Trackers; }

  void Register(ModifiedFieldTransceiver tracker) {
    if (!tracker) return;
    m_Trackers.Insert(tracker);
  }

  void Unregister(ModifiedFieldTransceiver tracker) {
    m_Trackers.RemoveItem(tracker);
  }

  bool DeleteByName(string name) {
    for (int i = m_Trackers.Count() - 1; i >= 0; i--) {
      if (m_Trackers[i] && m_Trackers[i].GetTrackerName() == name) {
        m_Trackers[i].Delete();
        m_Trackers.Remove(i);
        return true;
      }
    }
    return false;
  }

  void OnUpdate(float timeslice) {
      m_TimeAccu += timeslice;
      if (m_TimeAccu < m_Settings.updateInterval) return;

      m_TimeAccu = 0;
      BroadcastPositions();
    }

    string GetNearestLocationText(vector pos) {
    string closestName;
    float closestDistance = float.MAX;

    foreach (string name, vector locPos : m_Settings.landmarks) {
      float dist = vector.Distance(pos, locPos);
      if (dist < closestDistance) {
        closestDistance = dist;
        closestName = name;
      }
    }

    if (closestName == "")
      return "";

    string direction;
    float distance;
    GetDirectionAndDistance(m_Settings.landmarks.Get(closestName), pos, direction, distance);

    return string.Format("%1 m %2 of %3", Math.Round(distance), direction, closestName);
  }

  void BroadcastPositions(bool adminOverride = false) {
    array<Man> players = new array<Man>;
    GetGame().GetPlayers(players);

    BroadcastPositions(players, adminOverride);
  }

  void BroadcastPositions(Man player, bool adminOverride = false) {
    array<Man> players = {player};
    BroadcastPositions(players, adminOverride);
  }

  void BroadcastPositions(array<Man> players, bool adminOverride = false) {
    if (players.Count() == 0) return;

    foreach (ModifiedFieldTransceiver tracker : m_Trackers) {
      if (!tracker) continue;

      vector trackerPosition = tracker.GetPosition();

      int gridX, gridZ;
      GetGame().GetWorld().GetGridCoords(trackerPosition, 100, gridX, gridZ);
      PlayerBase holder = PlayerBase.Cast(tracker.GetHierarchyRootPlayer());

      string locationText = GetNearestLocationText(trackerPosition);

      foreach (Man man : players) {
        PlayerBase player = PlayerBase.Cast(man);
        if (!player) continue;
        if (!adminOverride && !m_Settings.includeHolder && player == holder) continue;

        vector playerPosition = player.GetPosition();
        string direction;
        float distance;
        GetDirectionAndDistance(playerPosition, trackerPosition, direction, distance);

        string msg = "[Tracker] " + tracker.GetTrackerName();

        if (adminOverride || m_Settings.gridInfo) msg += string.Format(" at X:%1 Y:%2", gridX, gridZ);

        if (adminOverride || m_Settings.playerInfo) {
          if (!adminOverride && distance <= m_Settings.minDistance) {
            msg += string.Format(" (you are within %1 m)", m_Settings.minDistance);
          } else {
            msg += string.Format(" (%1 m %2 of you)", Math.Round(distance), direction);
          }
        }

        if ((adminOverride || m_Settings.landmarkInfo) && locationText != "") {
          // Add comma only if something already added
          if (adminOverride || m_Settings.gridInfo || m_Settings.playerInfo) msg += ", ";
          else msg += " ";

          msg += locationText;
        }

        player.MessageImportant(msg);
      }
    }
  }
}
