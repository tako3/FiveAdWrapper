public import FiveAd

public func semanticVersion() -> String {
    FADAdLoader.semanticVersion()
}

public func registerFiveAd(appId: String) {
    let config = FADConfig(appId: appId) as FADConfig
#if FIVEAD_DEBUG
    config.isTest = true
#endif
    FADSettings.register(config)
}

public func loader(appId: String) throws -> FADAdLoader {
    let config = FADConfig(appId: appId) as FADConfig
#if FIVEAD_DEBUG
    config.isTest = true
#endif
    return try FADAdLoader(for: config)

}
