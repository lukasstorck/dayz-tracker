class ModifiedFieldTransceiver : BaseRadio {
  protected string m_TrackerName;

  void ModifiedFieldTransceiver() {
    SOUND_RADIO_TURNED_ON = "baseradio_staticnoise_SoundSet";
    SetCanBeDestroyed(false);

    if (!m_TrackerName || m_TrackerName.Length() == 0)
      m_TrackerName = GetID().ToString();
  }

  void SetTrackerName(string name) {
    m_TrackerName = name;
    SetSynchDirty();
  }

  string GetTrackerName() {
    return m_TrackerName;
  }

  override bool CanPutInCargo(EntityAI parent) {
    // disallow cars, might despawn
    if (parent.IsInherited(CarScript))
      return false;

    // disllow dead infected / bodies, might despawn
    if (!parent.IsAlive())
      return false;

    // disallow ruined storage items, might despawn
    if (parent.IsRuined())
      return false;

    return true;
  }

  override void EEInit() {
    super.EEInit();
    TrackerManager.Get().Register(this);
  }

  override void EEDelete(EntityAI parent) {
	  super.EEDelete(parent);
	  TrackerManager.Get().Unregister(this);
  }

  override void OnStoreSave(ParamsWriteContext ctx) {
	  super.OnStoreSave(ctx);
	  ctx.Write(m_TrackerName);
  }

  override bool OnStoreLoad(ParamsReadContext ctx, int version) {
    if (!super.OnStoreLoad(ctx, version))
      return false;

    if (!ctx.Read(m_TrackerName))
      m_TrackerName = "";

    return true;
  }
}

