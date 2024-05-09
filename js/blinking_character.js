const blinkingCharacter = document.getElementById('blinking-character');
let isBlinking = true;

setInterval(function() {
  if (isBlinking) {
    blinkingCharacter.innerHTML = '<span style="visibility: hidden;">_</span>';
  } else {
    blinkingCharacter.innerHTML = '_';
  }

  isBlinking = !isBlinking;
}, 500); // Toggle every 500 milliseconds (0.5 seconds)

