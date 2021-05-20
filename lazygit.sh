# 一次性处理git提交

# branch_name=$(git symbolic-ref --short -q HEAD)
if [ ! -n "$1" ] ;then
comment="update"
else
comment=$1
fi
echo "Add."
git add .
echo "Commit."
git commit -m "$comment"
echo "Push."
git push
echo "Finish."