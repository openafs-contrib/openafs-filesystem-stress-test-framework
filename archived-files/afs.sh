#!/bin/bash
echo ""
cd ..
tar -czvf openafs-fst.tar.gz openafs-filesystem-stress-test-framework
scp openafs-fst.tar.gz "$1"
ssh "$1"
