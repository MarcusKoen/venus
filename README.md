SETTING UP GIT

```
git init -b main 
git add .
git commit -m "first commit"
git config --global user.email "user@email.com"
git branch -M main
git remote add origin https://github.com/MarcusKoen/venus.git
git push -u origin main
```

GENERATING SSH
```
ssh-keygen -t ed25519 -C "your_email@example.com"
	USE PASSPHRASE OR NOT
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519
```
ADD SSH TO GITHUB
```
cat ~/.ssh/id_ed25519.pub
```
GitHub → Settings → SSH and GPG keys → New SSH key.

UPDATE AND PUSH ORIGIN
```
git remote set-url origin git@github.com:MarcusKoen/venus.git
git push -u origin main
```


General workflow

```
git add
git commit -m "note"
git push -u origin main
```
