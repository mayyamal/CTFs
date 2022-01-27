# SASD Course
In this course you take the role of a security consultant, who has been asked to audit multiple small C and C++ applications, let them be called ”hacklets” for the remainder of this document, for potential security issues. After a series of strange incidents, bad news coverage, and an increasing number of bug reports by angry users claiming loss of data and disclosure of private information due to security problems in the hacklets, you have been hired to audit the code. Note that your fictional employer in this scenario currently considers information security as a nice-to-have-butnot-mission-critical-if-missing feature.

##Flag format
All hacklets except some hacklets, as indicated below, use the following flag format SASD{[A-Za-z0-9_!]{26}}, e.g. SASD{TH1S_IS_A_local_TEST_FL4G!}.

##Test
… your exploit on the provided VM by running `./exploit` inside the hacklet directory. On success, it shall print the above demo flag to stdout. In addition, the exploit has to write the flag to a file named `solution.txt`.