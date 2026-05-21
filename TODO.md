# TODO

## Variables should be make working commands, 
### Example:
```bash 
export $ls='ls -a'
```

```bash
$ls
```

Output: 
A ls output with the argument (in this case, showing hidden files/folders)
```bash
. file.txt ...
```

## Word splitting
### This is required so commands can be executed within variables ^^^
When having variables with multiple values, example:
```
export dir="my dir""
```
bash will create 2 folders, the folder "my" and the folder "dir", and not a folder called "my dir".
