import FiveAd

public func semanticVersion() -> String {
    FADSettings.semanticVersion()
}

public func registerFiveAd(appId: String) {
    let config = FADConfig(appId: appId) as FADConfig
#if FIVEAD_DEBUG
    config.isTest = true
#endif
    FADSettings.register(config)
}
