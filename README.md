# 📋 To-Do List Manager (C)

A simple **command-line task manager** written in C.  
It allows you to **add**, **view**, **delete**, **toggle status**, and **save** tasks persistently in a text file.

---

## 🚀 Features

- ✅ Add a task  
- 📜 Show all tasks  
- ❌ Delete a task  
- 🔄 Toggle task status (done / not done)  
- 💾 Save tasks automatically in `tasks.txt`  
- 📂 Load tasks from file on startup  
- 🆘 Display command manual  

---

## 🛠️ How It Works

- Each task has:
  - A **text description**
  - A **status**:  
    - `0` → Not done  
    - `1` → Done  

- Tasks are stored in `tasks.txt` in this format:
  ```
  status;text
  0;Buy groceries
  1;Finish homework
  ```

- The program shows a menu where you can type either a **number** or a **command string**.

---

## 📖 Commands

| Command / Input | Action |
|-----------------|---------|
| `1` / `add` / `ADD` | Add a task |
| `2` / `show` / `SHOW` | Show all tasks |
| `3` / `del` / `DEL` | Delete a task |
| `4` / `tog` / `TOG` | Toggle task status |
| `5` / `quite` / `QUITE` | Save & Quit |
| `6` / `man` / `MAN` | Show command manual |

---

## 💻 Usage

### 1. Compile
```bash
gcc -o todo main.c
```

### 2. Run
```bash
./todo
```

### 3. Example
```
==== Liste des taches ====
1. Ajouter une tache
2. Afficher les taches
3. Supprimer une tache
4. Basculer l'etat de la tache 
5. Quitter (avec sauvegarde)
6. afficher le menu de commend

Votre choix : add
Entrez la tache: Learn C
Tache ajoutee!

Votre choix : show
1. [-] Learn C
```

---

## 📂 File Structure
```
.
├── main.c       # Source code
├── tasks.txt    # Tasks storage (auto-generated)
└── README.md    # Documentation
```

---

## ⚠️ Limitations
- Maximum of **100 tasks** (`MAX_TASKS = 100`)  
- Maximum length of each task: **256 characters** (`MAX_TASK = 256`)  

---

## ✨ Future Improvements
- Add support for editing a task text  
- Add search / filter functionality  
- Use JSON or SQLite instead of plain text  

---

## 👨‍💻 Author
Made with ❤️ in C.
