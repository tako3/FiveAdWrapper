// swift-tools-version: 6.1
import PackageDescription

let package = Package(
    name: "FiveAdWrapper",
    platforms: [
        .iOS(.v15),
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
            path: "Frameworks/FiveAd-v3.0.xcframework"
        ),
        .binaryTarget(
            name: "FiveGADAdapter",
            path: "Frameworks/FiveGADAdapter.xcframework"
        )
    ]
)
