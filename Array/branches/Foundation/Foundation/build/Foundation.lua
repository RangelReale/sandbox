--
-- Foundation.lua
--
-- Premake build script for POCO library (Foundation)
--
-- Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
-- and Contributors.
--
-- Permission is hereby granted, free of charge, to any person or organization
-- obtaining a copy of the software and accompanying documentation covered by
-- this license (the "Software") to use, reproduce, display, distribute,
-- execute, and transmit the Software, and to prepare derivative works of the
-- Software, and to permit third-parties to whom the Software is furnished to
-- do so, all subject to the following:
--
-- The copyright notices in the Software and this entire statement, including
-- the above license grant, this restriction and the following disclaimer,
-- must be included in all copies of the Software, in whole or in part, and
-- all derivative works of the Software, unless such copies or derivative
-- works are solely in the form of machine-executable object code generated by
-- a source language processor.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
-- SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
-- FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
-- ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
-- DEALINGS IN THE SOFTWARE.
--

package.language = "c++"
package.objdir = "../obj/Foundation"

if (options["target"] == "vs2003") then
	package.name = "Foundation".."_vs71"
elseif (options["target"] == "vs2005") then
	package.name = "Foundation".."_vs80"
elseif (options["target"] == "vs2008") then
	package.name = "Foundation".."_vs90"
else 
	package.name = "Foundation"
end

for k,v in ipairs(project.configs) do
    package.config[v].target=package.config[v].name
end

-- Append a "d" to the debug version of the libraries
package.config["debug_shared"].target= "PocoFoundationd"
package.config["release_shared"].target= "PocoFoundation"
package.config["debug_static"].target= "PocoFoundationmtd"
package.config["release_static"].target= "PocoFoundationmt"

-- Define _DEBUG/NDEBUG depending on build kind

for k,v in ipairs(project.configs) do
    if (string.find(v, "debug") ~= nil) then
        table.insert(package.config[v].defines, "_DEBUG")
    else
        -- Allow asserts to be included in release build by default
        --      table.insert(package.config[v].defines, "NDEBUG")
    end
end


-- Output is placed in a directory named for the target toolset.
-- package.path = options["target"]
package.path = "./" 

-- Package Build Settings

if (not options["enable-shared-only"]) then

    package.config["debug_static"].kind = "lib"
    package.config["release_static"].kind = "lib"
    table.insert(package.config["debug_static"].defines, "Foundation_EXPORTS")
    table.insert(package.config["debug_static"].defines, "POCO_STATIC")
    table.insert(package.config["debug_static"].defines, "PCRE_STATIC")
    table.insert(package.config["release_static"].defines, "Foundation_EXPORTS")
    table.insert(package.config["release_static"].defines, "POCO_STATIC")
    table.insert(package.config["release_static"].defines, "PCRE_STATIC")

end

if (not options["enable-static-only"]) then

    package.config["debug_shared"].kind = "dll"
    package.config["release_shared"].kind = "dll"
    table.insert(package.config["debug_shared"].defines, "_USRDLL")
    table.insert(package.config["debug_shared"].defines, "Foundation_EXPORTS")
    table.insert(package.config["debug_shared"].defines, "PCRE_STATIC")
    table.insert(package.config["release_shared"].defines, "_USRDLL")
    table.insert(package.config["release_shared"].defines, "Foundation_EXPORTS")
    table.insert(package.config["release_shared"].defines, "PCRE_STATIC")

end


package.includepaths =
{
    "../include"
}

if (windows) then
    table.insert(package.defines, "WIN32")
    table.insert(package.defines, "_WINDOWS")
end

-- disable VS2005 CRT security warnings
if (options["target"] == "vs2005" or options["target"] == "vs2008") then
    table.insert(package.defines, "_CRT_SECURE_NO_DEPRECATE")
end


-- Build Flags

package.config["debug_static"].buildflags   = { }
package.config["debug_shared"].buildflags   = { }

package.config["release_shared"].buildflags = { "optimize-speed", "no-symbols", "no-frame-pointer" }
package.config["release_static"].buildflags = { "optimize-speed", "no-symbols", "no-frame-pointer" }


-- Libraries

if (windows) then
    table.insert(package.links, "iphlpapi")
end

if (linux) then
    table.insert(package.links, "pthread")
end


-- Files
--
CPP_IncludedFiles =
{
	matchrecursive("../src/*_*.cpp")
}

WIN32_Files =
{
	matchrecursive("../src/*_WIN32.cpp"),
	matchrecursive("../src/*_WIN32U.cpp"),
}

POSIX_Files =
{
	matchrecursive("../src/*_POSIX.cpp"),
	matchrecursive("../src/*Opcom*.cpp"),
	matchrecursive("../src/*Syslog*.cpp"),
}

VMS_Files =
{
	matchrecursive("../src/*_VMS.cpp"),
}

Core_files =
{
    -- Add the include files recursively 
    --matchrecursive("./include/*.h"),
    --matchrecursive("./include/*.cpp"),

    -- Add the source recursively 
    --matchrecursive("./src/*.cpp"),
    --matchrecursive("./src/*.c")
	--
	--
    -- Add the include files recursively 
    matchrecursive("../include/*.h"),
    matchrecursive("../include/*.cpp"),

    -- Add the source recursively 
    matchrecursive("../src/*.cpp"),
    matchrecursive("../src/*.c")
}

Excluded_files =
{
	matchrecursive("../src/*_*.cpp"),
}


if (windows) then
    table.insert(package.defines, "WIN32")
    table.insert(package.defines, "_WINDOWS")

    table.insert(package.excludes, CPP_IncludedFiles)
--    table.insert(package.excludes, WIN32_Files)
	table.insert(package.excludes, POSIX_Files)
--    table.insert(package.excludes, VMS_Files)
end

if (not windows) then
    table.insert(package.excludes, WIN32_Files)
end

package.files = { Core_files }
--package.excludes = { Excluded_files }

