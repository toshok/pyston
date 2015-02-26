# skip-if: True

from django.conf import settings
if not settings.configured:
    settings.configure()
from django.template import Context, Template

t = Template(u"{{testvar}}")
print t.render(Context({"testvar":"hello world"}))
