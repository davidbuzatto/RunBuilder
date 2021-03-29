#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

int main() {

    //path startingPath( "C:/Program Files" );
    //path startingPath( "C:/" );
    std::vector<string> driveLetters;

    std::vector<path> gccPaths;
    std::vector<path> gppPaths;
    std::vector<path> javacPaths;
    std::vector<path> pythonPaths;

    path selectedGccPath;
    path selectedGppPath;
    path selectedJavacPath;
    path selectedPythonPath;

    int selectedGccPathIndex = -1;
    int selectedGppPathIndex = -1;
    int selectedJavacPathIndex = -1;
    int selectedPythonPathIndex = -1;
    int selectedDriveLetterIndex = 0;
    int current = 1;

    cout << "Hi student!" << endl <<
            "I'm a program developed by prof. David Buzatto!" << endl << endl <<

            "I will try to find JJudge binary dependencies" << endl <<
            "and create an simple application loader" << endl <<
            "based in your system's configuration." << endl << endl <<

            "That loader will be called run.bat" << endl <<
            "and will be created in the same" << endl <<
            "directory in which I'm being executed." << endl << endl <<

            "Let's get started! ;)" << endl << endl;


    for ( char c = 'A'; c <= 'Z'; c++ ) {
        string driveLetter = "";
        driveLetter += c;
        driveLetter += ":/";
        if ( exists( path( driveLetter ) ) ) {
            driveLetters.push_back( driveLetter );
        }
    }

    if ( driveLetters.size() > 1 ) {

        cout << "I found " << driveLetters.size() << " drives in your system." << endl <<
                "which one do you want me to use?" << endl;

        for ( int i = 1; i <= driveLetters.size(); i++ ) {
            cout << "    [" << i << "]: \"" << driveLetters[i-1] << "\"" << endl;
        }

        cout << "Please, select: ";
        cin >> selectedDriveLetterIndex;

        if ( selectedDriveLetterIndex <= 0 || selectedDriveLetterIndex > driveLetters.size() ) {
            selectedDriveLetterIndex = 0;
        } else {
            selectedDriveLetterIndex--;
        }

    }

    path startingPath( driveLetters[selectedDriveLetterIndex] );

    if ( exists( startingPath ) ) {

        try {
            if ( is_directory( startingPath ) ) {

                cout << "Looking for JJudge binary dependencies in \"" <<
                        driveLetters[selectedDriveLetterIndex] <<
                        "\"... please wait..." << endl;

                for ( directory_entry& entry : recursive_directory_iterator( startingPath, directory_options::skip_permission_denied ) ) {

                    if ( is_regular_file( entry ) ) {

                        path pOk = entry.path();

                        if ( pOk.filename() == "gcc.exe" ) {
                            gccPaths.push_back( pOk );
                        }

                        if ( pOk.filename() == "g++.exe" ) {
                            gppPaths.push_back( pOk );
                        }

                        if ( pOk.filename() == "javac.exe" ) {
                            javacPaths.push_back( pOk );
                        }

                        if ( pOk.filename() == "python.exe" ) {
                            pythonPaths.push_back( pOk );
                        }

                    }

                }

                cout << "Done!" << endl << endl;

                if ( gccPaths.size() != 0 ) {
                    cout << "I found " << gccPaths.size() << " gcc binary(ies):" << endl;
                    current = 1;
                    for ( path& path : gccPaths ) {
                        cout << "    [" << current++ << "]: " << path << endl;
                    }
                } else {
                    cout << "gcc.exe was not found!" << endl;
                }
                cout << endl;

                if ( gppPaths.size() != 0 ) {
                    cout << "I found " << gppPaths.size() << " g++ binary(ies):" << endl;
                    current = 1;
                    for ( path& path : gppPaths ) {
                        cout << "    [" << current++ << "]: " << path << endl;
                    }
                } else {
                    cout << "g++.exe was not found!" << endl;
                }
                cout << endl;

                if ( javacPaths.size() != 0 ) {
                    cout << "I found " << javacPaths.size() << " javac binary(ies):" << endl;
                    current = 1;
                    for ( path& path : javacPaths ) {
                        cout << "    [" << current++ << "]: " << path << endl;
                    }
                } else {
                    cout << "javac.exe was not found!" << endl;
                }
                cout << endl;

                if ( pythonPaths.size() != 0 ) {
                    cout << "I found " << pythonPaths.size() << " python binary(ies):" << endl;
                    current = 1;
                    for ( path& path : pythonPaths ) {
                        cout << "    [" << current++ << "]: " << path << endl;
                    }
                } else {
                    cout << "python.exe was not found!" << endl;
                }
                cout << endl;

                if ( gccPaths.size() == 1 ) {
                    selectedGccPathIndex = 0;
                    selectedGccPath = gccPaths[selectedGccPathIndex];
                } else if ( gccPaths.size() > 1 ) {
                    cout << "Which gcc binary do you want to use?" << endl;
                    current = 1;
                    for ( path& path : gccPaths ) {
                        cout << "    [" << current++ << "]: " << path << endl;
                    }
                    cout << "Please, select: ";
                    cin >> selectedGccPathIndex;
                    selectedGccPathIndex--;
                    if ( selectedGccPathIndex < 0 || selectedGccPathIndex >= gccPaths.size() ) {
                        selectedGccPathIndex = 0;
                    }
                    selectedGccPath = gccPaths[selectedGccPathIndex];
                    cout << endl;
                }

                if ( gppPaths.size() == 1 ) {
                    selectedGppPathIndex = 0;
                    selectedGppPath = gppPaths[selectedGppPathIndex];
                } else if ( gppPaths.size() > 1 ) {
                    cout << "Which g++ binary do you want to use?" << endl;
                    current = 1;
                    for ( path& path : gppPaths ) {
                        cout << "    [" << current++ << "]: " << path << endl;
                    }
                    cout << "Please, select: ";
                    cin >> selectedGppPathIndex;
                    selectedGppPathIndex--;
                    if ( selectedGppPathIndex < 0 || selectedGppPathIndex >= gppPaths.size() ) {
                        selectedGppPathIndex = 0;
                    }
                    selectedGppPath = gppPaths[selectedGppPathIndex];
                    cout << endl;
                }

                if ( javacPaths.size() == 1 ) {
                    selectedJavacPathIndex = 0;
                    selectedJavacPath = javacPaths[selectedJavacPathIndex];
                } else if ( javacPaths.size() > 1 ) {
                    cout << "Which javac binary do you want to use?" << endl;
                    current = 1;
                    for ( path& path : javacPaths ) {
                        cout << "    [" << current++ << "]: " << path << endl;
                    }
                    cout << "Please, select: ";
                    cin >> selectedJavacPathIndex;
                    selectedJavacPathIndex--;
                    if ( selectedJavacPathIndex < 0 || selectedJavacPathIndex >= javacPaths.size() ) {
                        selectedJavacPathIndex = 0;
                    }
                    selectedJavacPath = javacPaths[selectedJavacPathIndex];
                    cout << endl;
                }

                if ( pythonPaths.size() == 1 ) {
                    selectedPythonPathIndex = 0;
                    selectedPythonPath = pythonPaths[selectedPythonPathIndex];
                } else if ( pythonPaths.size() > 1 ) {
                    cout << "Which python binary do you want to use?" << endl;
                    current = 1;
                    for ( path& path : pythonPaths ) {
                        cout << "    [" << current++ << "]: " << path << endl;
                    }
                    cout << "Please, select: ";
                    cin >> selectedPythonPathIndex;
                    selectedPythonPathIndex--;
                    if ( selectedPythonPathIndex < 0 || selectedPythonPathIndex >= pythonPaths.size() ) {
                        selectedPythonPathIndex = 0;
                    }
                    selectedPythonPath = pythonPaths[selectedPythonPathIndex];
                    cout << endl;
                }

                cout << "Ok, now I will build the run.bat loader" << endl <<
                        "with the options that you selected..." << endl << endl;

                std::ofstream outfile( "run.bat" );

                outfile << "@ECHO OFF" << endl << endl;

                if ( selectedGccPathIndex != -1 ) {
                    outfile << "SET GCC_PATH=" << selectedGccPath.parent_path().string().replace( 2, 1, "\\" ) << endl;
                }

                if ( selectedGppPathIndex != -1 ) {
                    outfile << "SET GPP_PATH=" << selectedGppPath.parent_path().string().replace( 2, 1, "\\" ) << endl;
                }

                if ( selectedJavacPathIndex != -1 ) {
                    outfile << "SET JDK_PATH=" << selectedJavacPath.parent_path().string().replace( 2, 1, "\\" ) << endl;
                }

                if ( selectedPythonPathIndex != -1 ) {
                    outfile << "SET PYTHON_PATH=" << selectedPythonPath.parent_path().string().replace( 2, 1, "\\" ) << endl;
                }

                outfile << endl;

                if ( selectedGccPathIndex != -1 ) {
                    outfile << "IF EXIST \"%GCC_PATH%\" SET PATH=%PATH%;%GCC_PATH%" << endl;
                }

                if ( selectedGppPathIndex != -1 ) {
                    outfile << "IF EXIST \"%GPP_PATH%\" SET PATH=%PATH%;%GPP_PATH%" << endl;
                }

                if ( selectedJavacPathIndex != -1 ) {
                    outfile << "IF EXIST \"%JDK_PATH%\" SET PATH=%PATH%;%JDK_PATH%" << endl;
                }

                if ( selectedPythonPathIndex != -1 ) {
                    outfile << "IF EXIST \"%PYTHON_PATH%\" SET PATH=%PATH%;%PYTHON_PAT%" << endl;
                }

                outfile << endl;

                if ( selectedJavacPathIndex != -1 ) {
                    outfile << "START \"\" \"" << selectedJavacPath.parent_path().string().replace( 2, 1, "\\" ) << "\\javaw.exe\" -jar JJudge.jar";
                }

                outfile.close();

                cout << "Done!" << endl;
                cout << "Bye ;)" << endl;

                system( "PAUSE" );

            } else {
                cout << startingPath << " the path must be a directory!" <<
                        endl << "aborting..." << endl;
            }
        } catch ( const filesystem_error& exc ) {
            cout << exc.what() << endl;
        }
    } else {
        cout << startingPath << " does not exists." << endl << "aborting..." << endl;
    }

    return 0;
}
