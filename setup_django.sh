

set -eu
set -x

make pyston_dbg
./pyston_dbg test/tests/django_setup.py
./pyston_dbg testsite/manage.py startapp blog
mv blog testsite

cat >>testsite/blog/models.py <<EOF
class Post(models.Model):
    title = models.CharField(max_length=200)
EOF

sed -i "s/INSTALLED_APPS = (/INSTALLED_APPS =('blog',/" testsite/testsite/settings.py
./pyston_dbg testsite/manage.py makemigrations blog
./pyston_dbg testsite/manage.py migrate
./pyston_dbg testsite/manage.py createsuperuser
./pyston_dbg testsite/manage.py runserver --noreload
