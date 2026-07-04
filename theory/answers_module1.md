# Module 1 Theory Solutions

## Q9. Explain the difference between git pull, git fetch, and git clone. When would you use each?
- **git clone**: Downloads an entire remote repository from scratch, generating a complete local tracking directory linked to the remote server configuration on your computer.
  * *When to use:* Used when you want to copy an assignment repository onto your workstation for the very first time.
- **git fetch**: Pulls down all the latest references, branches, and commit histories from the remote cloud server, but does NOT modify or automatically merge those changes into your local files.
  * *When to use:* Used when you want to securely inspect what updates your peers have pushed to the cloud before integrating them.
- **git pull**: Instantly fetches updates from the remote tracking system and automatically runs a merge directly into your current active local tracking branch.
  * *When to use:* Used when you want to rapidly synchronize your local working files with changes on the remote repository.

## Q10. What is a .gitignore file?
A `.gitignore` file is a plain text configuration file placed in the repository root that specifies exactly which files, file patterns, or directories Git should intentionally skip tracking.

In IoT and embedded systems engineering, it is highly critical to exclude bulky, auto-generated compiler output artifacts (like `.hex` and `.elf` binaries), local IDE metadata states (`.vscode/` or `build/`), and secret network configuration files containing private Wi-Fi API keys or credentials. This keeps the public repository history lightweight, clean, and secure.
