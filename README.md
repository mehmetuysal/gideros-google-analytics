# Gideros Google Analytics

Gideros google analytics ios plugin.

- Follow the instruction https://developers.google.com/analytics/devguides/collection/ios/v3/?hl=en
- Copy plugin files to xcode plugin directory
- That's it!

 You need to use GoogleServer-info.plist instead of "startAnalytics" first parameter APP_ID_FROM_CONFIG. This parameter will be impletemented soon.

        require "analytics"

        -- analytics.startAnalytics("APP_ID",crash_and_exceptions)
        -- START ANALYTICS
        analytics.startAnalytics("APP_ID_FROM_CONFIG",true)

        -- SEND SCREEN NAME
        analytics.sendScreen("Game Menu Screen")

        -- SEND EVENT
        -- analytics.sendEvent("Event Category","Event Action","Event Label",Value)
        analytics.sendEvent("Menu","Pressed","Button Name",1)