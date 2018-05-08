#!/bin/sh

export CPPCHECK_DEFINITIONS="-DCOMMON_FILE_COMPRESS_GZ -DCOMMON_PTHREAD -DCOMMON_RANDOM_FIXED_SEED -DSCOTCH_RENAME -DSCOTCH_PTHREAD -Drestrict=__restrict -DIDXSIZE64"
export CPPCHECK_INCLUDES="-Isrc/scotch -Isrc/misc -Isrc/libscotch -Isrc/esmumps -Isrc/libscotchmetis"
./.gitlab-ci-filelist.sh

cppcheck -v --max-configs=1 --language=c --platform=unix64 --enable=all --xml --xml-version=2 --suppress=missingIncludeSystem --suppress=varFuncNullUB --suppress=invalidPrintfArgType_sint ${CPPCHECK_DEFINITIONS} ${CPPCHECK_INCLUDES} --file-list=./filelist.txt 2> scotch-cppcheck.xml

rats -w 3 --xml `cat filelist.txt` > scotch-rats.xml

cat > sonar-project.properties << EOF
sonar.host.url=https://sonarqube.bordeaux.inria.fr/sonarqube
sonar.login=$SONARQUBE_LOGIN
sonar.links.homepage=https://gitlab.inria.fr/scotch/scotch
sonar.links.scm=https://gitlab.inria.fr/scotch/scotch.git
sonar.links.ci=https://gitlab.inria.fr/scotch/scotch/pipelines
sonar.links.issue=https://gitlab.inria.fr/scotch/scotch/issues
sonar.projectKey=tadaam:scotch:gitlab:master
sonar.projectDescription=Package for graph and mesh/hypergraph partitioning, graph clustering, and sparse matrix ordering.
sonar.projectVersion=6.0
sonar.language=c
sonar.sourceEncoding=UTF-8
sonar.sources=include,src/check,src/esmumps,src/libscotch,src/libscotchmetis,src/misc,src/scotch
sonar.c.includeDirectories=$(echo | gcc -E -Wp,-v - 2>&1 | grep "^ " | tr '\n' ',')include,src/scotch,src/misc,src/libscotch,src/esmumps,src/libscotchmetis
sonar.c.errorRecoveryEnabled=true
sonar.c.compiler.charset=UTF-8
sonar.c.compiler.parser=GCC
sonar.c.compiler.regex=^(.*):(\\\d+):\\\d+: warning: (.*)\\\[(.*)\\\]$
sonar.c.compiler.reportPath=scotch-build.log
sonar.c.coverage.reportPath=scotch-coverage.xml
sonar.c.cppcheck.reportPath=scotch-cppcheck.xml
sonar.c.rats.reportPath=scotch-rats.xml
sonar.c.clangsa.reportPath=analyzer_reports/*/*.plist
EOF