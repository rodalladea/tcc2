import { createGlobalStyle } from 'styled-components';

export default createGlobalStyle`
    * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
    }
    html, body {
        width: 100%;
        height: 100%;
        min-height: 100%;
    }
    body {
        background: #f2f2f2;
        color: #24292e;
        -webkit-font-smoothing: antialiased;
    }
    body, input, button {
        font-family: 'Roboto', sans-serif;
        font-size: 16px;
        outline: none;
    }
    h1, h2, h3, h4, h5, h6, strong {
        font-weight: 500;
    }
    button {
        cursor: pointer;
    }
`;
