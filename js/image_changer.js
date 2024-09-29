const images = [
    '../resources/gesture_control.png',
    '../resources/auto-targeting_old_2.png',
];

let currentIndex = 0;

const displayedImage = document.getElementById('changable_image');
const nextButton = document.getElementById('flip_button');

nextButton.addEventListener('click', () => {
    currentIndex = (currentIndex + 1) % images.length; // Cycle through images
    displayedImage.src = images[currentIndex];
});
