// swift-tools-version: 6.1
import PackageDescription

let package = Package(
    name: "FiveAdWrapper",
    platforms: [
        .iOS(.v13),
    ],
    products: [
        .library(name: "FiveAdWrapper", targets: ["FiveAdWrapper"]),
    ],
    targets: [
        .target(
            name: "FiveAdWrapper",
            dependencies: [
                .target(name: "FiveAd"),
                .target(name: "FiveGADAdapter"),
            ],
            swiftSettings: [
                .define("FIVEAD_DEBUG", .when(configuration: .debug))
            ],
            linkerSettings: [
                .linkedFramework("AdSupport"),
                .linkedFramework("AppTrackingTransparency"),
                .linkedFramework("AVFoundation"),
                .linkedFramework("CoreMedia"),
                .linkedFramework("CoreTelephony"),
                .linkedFramework("Network"),
                .linkedFramework("AudioToolbox"),
                .linkedFramework("WebKit"),
                .linkedFramework("StoreKit"),
            ]
        ),
        .binaryTarget(
            name: "FiveAd",
            path: "Frameworks/FiveAd-20250825.xcframework"
        ),
        .binaryTarget(
            name: "FiveGADAdapter",
            path: "Frameworks/FiveGADAdapter-v1.5.1.xcframework"
        )
    ]
)
