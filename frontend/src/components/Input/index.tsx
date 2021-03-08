import React, { InputHTMLAttributes, useState, useCallback } from 'react';

import Container from './styles';

interface InputProps extends InputHTMLAttributes<HTMLInputElement> {
    placeholder: string;
}

const Input: React.FC<InputProps> = ({ placeholder, ...rest }) => {
    const [isFocused, setIsFocused] = useState(false);

    const handleInputFocus = useCallback(() => {
        setIsFocused(true);
    }, []);

    const handleInputBlur = useCallback(() => {
        setIsFocused(false);
    }, []);

    return (
        <Container isFocused={isFocused}>
            <input onFocus={handleInputFocus} onBlur={handleInputBlur} type="text" placeholder={placeholder} onChange={rest.onChange} />
        </Container>
    );
};

export default Input;
