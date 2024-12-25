# {{ item.label }}
## Description
{{ item.description }}
## Requirements
{% for requirement in item.requirements -%}
- {{ requirement.label }}: {{ requirement.description }}
{% endfor -%}
## Ports
{% for port in item.ports -%}
### {{ port.label }}
- **Direction**: {{ port.direction }}
- **Interface**: {{ port.interface.label }}
{% endfor -%}
## Components
{% if item.Components|length == 0 -%}
No sub-components.
{% else -%}
{% for comp in item.Components -%}
- {{ comp.label }}: {{ comp.description }}
{% endfor -%}
{% endif -%}