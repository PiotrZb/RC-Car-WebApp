import * as React from 'react';
import Box from '@mui/material/Box';
import Slider from '@mui/material/Slider';

function valuetext(value) {
  return `${value}`;
}

function SpeedSlider({ onChange, value }) {
  return (
    <Box sx={{ width: 300 }}>
      <Slider
        aria-label="Power"
        defaultValue={200}
        getAriaValueText={valuetext}
        valueLabelDisplay="auto"
        shiftStep={4}
        step={4}
        marks
        min={200}
        max={240}
        onChange={onChange}
        value={value}
      />
    </Box>
  );
}

export default SpeedSlider;