function hideIframe(textContainerId, iframeId, url) {
  const iframe = document.getElementById(iframeId);
  const textContainer = document.getElementById(textContainerId);

  function loadIframe() {
    iframe.src = url;
    textContainer.style.display = 'none';
    iframe.removeEventListener('mouseenter', loadIframe);
  }

  function unloadIframe() {
    iframe.src = '';
    textContainer.style.display = 'block';
    iframe.addEventListener('mouseenter', loadIframe);
  }

  // iframe.addEventListener('mouseenter', loadIframe);
  iframe.addEventListener('mouseenter', loadIframe);
  iframe.addEventListener('mouseleave', unloadIframe);
}
