// script that toggles the color of a 'clickable-heading'
const heading = document.getElementById('clickable-heading');
let isRed = true;

heading.addEventListener('click', function() {
    if (!isRed) {
        heading.style.color = 'black';
    } else {
        heading.style.color = 'red';
    }
    
    isRed = !isRed;
});
