require "analytics"

-- analytics.startAnalytics("APP_ID",crash_and_exceptions)
-- START ANALYTICS
analytics.startAnalytics("APP_ID_FROM_CONFIG",true)

-- SEND SCREEN NAME
analytics.sendScreen("Game Menu Screen")

-- SEND EVENT
-- analytics.sendEvent("Event Category","Event Action","Event Label",Value)
analytics.sendEvent("Menu","Pressed","Button Name",1)