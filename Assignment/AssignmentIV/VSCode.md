# 使用 VSCode 連接 GitHub

## 前置需求
開始之前，請確保你已具備以下項目：
- 已在電腦上安裝 Visual Studio Code（VSCode）。[點此下載 VS Code](https://code.visualstudio.com/)
- 已安裝並設定 Git。[點此下載 Git](https://git-scm.com/)
- 擁有 GitHub 帳號。

## VSCode 中的環境
- 我的 VSCode 環境為 WSL: Ubuntu

## 連接到 GitHub 的步驟
### 1. 安裝 GitHub 擴充套件
- 開啟 VSCode。
- 點選左側活動列（Activity Bar）的擴充套件圖示。
- 搜尋「GitHub Pull Requests and Issues」並安裝該擴充套件。

### 2. 登入 GitHub
- 打開命令選單（Command Palette）：按 `Ctrl+Shift+P`（macOS 為 `Cmd+Shift+P`）。
- 輸入 `GitHub: Sign in` 並選擇該項目。
- 依照畫面指示完成 GitHub 登入驗證。

### 3. Clone（複製）儲存庫
- 在 VSCode 打開命令選單(Ctrl+Shift+P)。
- 輸入 `Git: Clone` 並選擇該選項。
- 選擇 circleaa/11401_CS203A 這個 GitHub 網址。
- 選擇儲存庫要複製到本機的資料夾。

### 4. 開啟儲存庫
- 儲存庫複製完成後，VSCode 會詢問是否要開啟。
- 點擊「Open（開啟）」開始使用專案。

### 5. 進行修改並儲存
- 依需要編輯儲存庫內的檔案，編輯完記得在檔案總管按儲存。
- 前往 VSCode 左側的原始碼控制（Source Control）。
- 將變更加入暫存區（Stage）。

### 6. 上傳修改的檔案至 GitHub
- 選擇要上傳到 GitHub 的資料夾(檔案)。
```bash
  git add Assignment/AssignmentIV
```
- 撰寫提交訊息並提交（Commit）。
```bash
  git commit -m "command..."
```
- 將變更推送（Push）至 GitHub。
```bash
  git push origin main --force
```
