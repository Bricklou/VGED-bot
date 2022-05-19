add_rules("mode.debug", "mode.release")

add_repositories("local-repo xmake/repo")

add_requires("fmt", "dpp", "nlohmann_json", "json-schema-validator", "spdlog", { configs = { shared = true }})
add_requireconfs("spdlog", { configs = { fmt_external = true }, system = false })

target("vged-bot")
    set_kind("binary")

    set_version("1.0.0")
    set_default(true)

    set_languages("cxx20")
    add_rpathdirs("$ORIGIN", "$ORIGIN/lib")

    set_installdir("./export")

    -- Sources
    add_files("src/**.cpp")
    add_headerfiles("src/**.hpp")

    before_install(function(target)
            os.rm(target:installdir())
    end)

    after_install(function(target)
            import("core.project.project")
            os.mv(target:installdir().."/bin/"..project.name(), target:installdir())
            os.rm(target:installdir().."/bin")
    end)

    add_packages("dpp", "spdlog", "fmt", "nlohmann_json", "json-schema-validator")

    if is_mode("debug") then
        add_defines("SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE")
    end

