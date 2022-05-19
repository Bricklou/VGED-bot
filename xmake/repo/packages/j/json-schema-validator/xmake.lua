package("json-schema-validator")
    set_homepage("https://github.com/pboettch/json-schema-validator")
    set_description("JSON schema validator for JSON for Modern C++ ")

    add_urls("https://github.com/pboettch/json-schema-validator.git")
    add_versions("2.1.0", "27fc1d094503623dfe39365ba82581507524545c")

    add_deps("cmake")

    on_load(function (package)
        package:add("deps", "nlohmann_json", { configs = { shared = package:config("shared") }})
    end)

    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE="..(package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS="..(package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs)
    end)
