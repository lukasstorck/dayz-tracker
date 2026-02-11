modded class MissionServer {
  override void OnUpdate(float timeslice) {
    super.OnUpdate(timeslice);
    TrackerManager.Get().OnUpdate(timeslice);
  }
}
