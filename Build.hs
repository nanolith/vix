import Development.Shake
import Development.Shake.Command
import Development.Shake.FilePath
import Development.Shake.Util

buildLibrary :: String -> Action [FilePath] -> FilePath -> Action ()
buildLibrary buildType ccs out = do
    cs <- ccs
    let os = ["_build" </> buildType </> c -<.> "o" | c <- cs]
    need os
    cmd "ar -rcs" [out] os

buildCxxObject :: String -> FilePath -> Action ()
buildCxxObject compileFlags out = do
    let c = dropDirectory1 $ dropDirectory1 $ out -<.> "cpp"
    let m = out -<.> "m"
    () <- cmd "clang++" compileFlags "-c" [c] "-o" [out] "-MMD -MF" [m]
    needMakefileDependencies m

main :: IO ()
main = shakeArgs shakeOptions{shakeFiles="_build/"} $ do
    want ["_build/release/libvix" <.> "a"]
    want ["_build/checked/libvix" <.> "a"]
    want ["_build/test/coverage-report/index.html"]

    let gtestDir = ".." </> "gtest"
    let checkedCxxflags = "--coverage -std=c++11 -stdlib=libc++ -O0 -I ./include -I " ++ (gtestDir </> "include") ++ " -I " ++ gtestDir
    let releaseCxxflags = "-std=c++11 -stdlib=libc++ -O3 -I ./include"

    phony "clean" $ do
        removeFilesAfter "_build" ["//*"]

    --the release library
    "_build/release/libvix" <.> "a" *> (buildLibrary "release" $ getDirectoryFiles "" ["src//*.cpp"])

    --the checked library
    "_build/checked/libvix" <.> "a" *> (buildLibrary "checked" $ getDirectoryFiles "" ["src//*.cpp"])

    --build an object file for release
    "_build/release//*.o" *> (buildCxxObject releaseCxxflags)

    --build an object file for checked
    "_build/checked//*.o" *> (buildCxxObject checkedCxxflags)

    --test targets

    let ldflags = ""
    let testlink = "-lstdc++ -L _build/checked -lvix " ++ (gtestDir </> "src" </> "gtest-all.cc")

    "_build/test/coverage-report/index.html" *> \out -> do
        need ["_build/checked/libvix" <.> "a"]
        need ["_build/test/vixtest" <.> exe]

        () <- cmd "mkdir -p _build/test/coverage-report"
        () <- cmd "lcov -no-external -b . --directory _build --zerocounters"
        () <- cmd "_build/test/vixtest"
        () <- cmd "lcov -no-external -b . --directory _build --capture --output-file _build/test/coverage-report/libvix.info"
        cmd "genhtml --no-branch-coverage -o _build/test/coverage-report _build/test/coverage-report/libvix.info"

    "_build/test/vixtest" <.> exe *> \out -> do
        cs <- getDirectoryFiles "" ["test//*.cpp"]
        let os = ["_build" </> "checked" </> c -<.> "o" | c <- cs]
        need os
        cmd "clang++" checkedCxxflags ldflags "-o" [out] os testlink
