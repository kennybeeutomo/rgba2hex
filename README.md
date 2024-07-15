# rgba2hex
Reads from stdin and replaces any rgba to hex *rgba(r,g,b,a) to #rrggbbaa* then outputs to stdout

### Example:

example.css:
```css
* {
    my-color: rgba(100, 120, 255, 100%);
}
```
then run:
```bash
cat example.css | rgba2hex
```
outputs:
```css
* {
    my-color: #6478FFFF;
}
```

### Usage:
Usage:
```bash
cat <file> | rgba2hex
```
or
```bash
cat <file> | rgba2hex <format>
```
```
<format> = xxxx
```
> where x can be 'd' or 'p'\
> d = decimal (0-255)\
> p = percentage (0-100%)\
> default format is 'dddp' if <format> is omitted

Example:
```bash
cat file | rgba2hex dddp
```
