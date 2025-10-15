#!/bin/bash

# 현재 디렉토리 위치 저장
CURRENT_DIR="$HOME/Library/CloudStorage/Dropbox/programming/study/DoitAlgorithm"

# main, main.exe 및 main.dSYM 파일/디렉터리를 찾아서 삭제하는 함수
cleanup_main_files() {
  echo "다음 파일 및 디렉터리가 삭제됩니다:"
  # 파일 목록 표시
  find "$CURRENT_DIR" -type f \( -name "main" -o -name "main.exe" \) | sort
  # main.dSYM 디렉터리 목록 표시
  find "$CURRENT_DIR" -type d -name "main.dSYM" | sort
  
  echo -e "\n계속 진행하시겠습니까? (y/n)"
  read -r response
  
  if [[ "$response" =~ ^[Yy]$ ]]; then
    # 파일 삭제 수행
    find "$CURRENT_DIR" -type f \( -name "main" -o -name "main.exe" \) -delete
    # main.dSYM 디렉터리 삭제 수행
    find "$CURRENT_DIR" -type d -name "main.dSYM" -exec rm -rf {} \; 2>/dev/null
    echo "삭제가 완료되었습니다."
  else
    echo "작업이 취소되었습니다."
  fi
}

# 스크립트 실행
echo "DoitAlgorithm 디렉토리에서 'main', 'main.exe' 파일과 'main.dSYM' 디렉터리를 찾아 삭제합니다."
echo "단, 'main.cpp', 'main.py', 'main.java' 파일은 보존됩니다."
echo ""

cleanup_main_files