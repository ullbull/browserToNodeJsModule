  if (argc == 1) {
    cout << "Oops! You didn't give me a file to work on." << endl;
    exit(1);
  }
  string inFileName = argv[1];
  string suffix = "_njs";
  if (argc == 3) suffix = argv[2];
  string outFileName = getNewFileName(inFileName, suffix);

  cout << "Let's go!" << endl;

  cout << inFileName << endl;
  cout << outFileName << endl;
  exit(0);