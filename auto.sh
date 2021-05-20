# branch_name=$(git symbolic-ref --short -q HEAD)
if [ ! -n "$1" ] ;then
comment="Too lazy to type comment."
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