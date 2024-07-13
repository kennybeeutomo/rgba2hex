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
